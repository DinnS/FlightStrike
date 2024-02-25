#include "stdafx.h"
#include "GameState.h"

/*         INITIALIZE FUNCTION         */

void GameState::initDeferredRender() {
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView() {
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/Timeless.ttf")) {
		throw("ERROR::GameState::COULD NOT LOAD FONT");
	}
}

void GameState::initPauseMenu() {
	const sf::VideoMode& videoMode = this->stateData->gfxSettings->resolution;
	
	this->pauseMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pauseMenu->addButton(
		"QUIT", gui::percentToPixelY(75.f, videoMode),
		gui::percentToPixelX(13.f, videoMode), gui::percentToPixelY(6.f, videoMode),
		gui::calcCharSize(50, videoMode),
		"Quit"
	);
}

void GameState::initPlayer() {
	this->player = new Player(0, 0);
}

void GameState::initMap() {
	this->background.setSize(
		sf::Vector2f(
			1000,
			1000
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Graphics/Game/Map.jpg")) {
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setFillColor(sf::Color::Color(228, 211, 184));
	this->background.setPosition(0,0);
	//this->background.setTexture(&this->backgroundTexture);
	
}

void GameState::initBolts() {
	this->bolts.emplace_back(200, 100);
}

/*       CONSTRUCTORS/DESTRUCTORS      */

GameState::GameState(StateData* state_data) : State(state_data) {
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initPauseMenu();
	this->initMap();
	this->initPlayer();
	this->initBolts();
}

GameState::~GameState() {
	delete this->pauseMenu;
	delete this->player;
}

/*				FUNCTION               */

// Update

void GameState::updateView() {
	// Default camera view
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (this->player->getHitboxComponentWidth() / 2)),
		std::floor(this->player->getPosition().y + (this->player->getHitboxComponentHeight() / 2))
	);

	// Dynamic camera view
	/*
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 6.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 6.f)
	);
	*/
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->pause) {
			this->pauseState();
		}
		else {
			this->unpauseState();
		}
	}

}

void GameState::updatePlayerInput(const float& dt)
{
	// Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->movementDirection.x = -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->movementDirection.x = 1.f;
	}
	else {
		this->movementDirection.x = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->movementDirection.y = -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->movementDirection.y = 1.f;
	}
	else {
		this->movementDirection.y = 0.f;
	}

	this->player->move(this->movementDirection.x, this->movementDirection.y, dt);

}

void GameState::updatePauseMenuButtons() {
	if (this->pauseMenu->isButtonPressed("QUIT")) {
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	if (!this->pause) {
		this->updateView();
		this->updatePlayerInput(dt);

		this->player->update(dt);

		/*if(this->player)
		this->bolts[0].update();*/
	}
	else {
		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

// Render
void GameState::renderMap(sf::RenderTarget* target) {
	target->draw(this->background);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	this->renderTexture.clear();

	

	this->renderTexture.setView(this->view);

	this->renderMap(&this->renderTexture);
	

	this->player->render(this->renderTexture);

	this->bolts[0].render(this->renderTexture);

	// Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	

	if (this->pause) {
		this->pauseMenu->render(this->renderTexture);
	}

	// Final render
	this->renderTexture.display();
	target->draw(this->renderSprite);
}
