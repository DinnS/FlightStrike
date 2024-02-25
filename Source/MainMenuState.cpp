#include "stdafx.h"
#include "MainMenuState.h"

/*         INITIALIZE FUNCTION         */

void MainMenuState::initVariables() {
	
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Timeless.ttf")) {
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	// Init keys for MainMenuState
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initGui()
{
	const sf::VideoMode& videoMode = this->stateData->gfxSettings->resolution;
	
	// Buttons
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::percentToPixelX(10.f, videoMode), gui::percentToPixelY(30.f, videoMode),
		gui::percentToPixelX(13.f, videoMode), gui::percentToPixelY(6.f, videoMode),
		&this->font, "New Game", gui::calcCharSize(60, videoMode),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::percentToPixelX(10.f, videoMode), gui::percentToPixelY(60.f, videoMode),
		gui::percentToPixelX(13.f, videoMode), gui::percentToPixelY(6.f, videoMode),
		&this->font, "Quit", gui::calcCharSize(60, videoMode),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

/*       CONSTRUCTORS/DESTRUCTORS      */

MainMenuState::MainMenuState(StateData* state_data) : State(state_data) {
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState() {
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i) {
		delete i->second;
	}
}

/*				FUNCTION               */

void MainMenuState::resetGui() {
	/*
	*  Clear GUI elements and re-initializes the GUI
	*
	*  @return		void
	*/
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i) {
		delete i->second;
	}

	this->initGui();
}

// Update
void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	// Updates all buttons
	for (auto i : this->buttons) {
		i.second->update(this->mousePosWindow);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(this->stateData));
	}

	// Quit
	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->endState();
	}
}

void MainMenuState::update(const float& dt) {
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
	/*
	system("cls");
	std::cout << "mousePosScreen : " << this->mousePosScreen.x << "  " << this->mousePosScreen.y << std::endl;
	std::cout << "mousePosWindow : " << this->mousePosWindow.x << "  " << this->mousePosWindow.y << std::endl;
	std::cout << "mousePosView : " << this->mousePosView.x << "  " << this->mousePosView.y << std::endl;
	*/
}

// Render
void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons) {
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {
	if (!target) {
		target = this->window;
	}

	this->renderButtons(*target);
}


