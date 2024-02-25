#include "stdafx.h"
#include "Player.h"

/*         INITIALIZE FUNCTION         */

void Player::initVariables() {
	
}

void Player::initTextureSheet() {
	this->textureSheet["IDLE"] = new sf::Texture();
	if (!this->textureSheet["IDLE"]->loadFromFile("Resources/Graphics/Game/Plane.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE";
	}

	this->textureSheet["MOVING_TOP"] = new sf::Texture();
	if (!this->textureSheet["MOVING_TOP"]->loadFromFile("Resources/Graphics/Game/top.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_MOVING_TOP";
	}

	this->textureSheet["MOVING_DOWN"] = new sf::Texture();
	if (!this->textureSheet["MOVING_DOWN"]->loadFromFile("Resources/Graphics/Game/down.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_MOVING_DOWN";
	}

	this->textureSheet["MOVING_RIGHT"] = new sf::Texture();
	if (!this->textureSheet["MOVING_RIGHT"]->loadFromFile("Resources/Graphics/Game/right.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_MOVING_RIGHT";
	}

	this->textureSheet["MOVING_LEFT"] = new sf::Texture();
	if (!this->textureSheet["MOVING_LEFT"]->loadFromFile("Resources/Graphics/Game/left.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_MOVING_LEFT";
	}

	this->setTexture(*this->textureSheet["IDLE"]);
}

void Player::initComponents()
{
	this->createHitboxComponent(this->sprite, 0.f, 0.f, this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
	this->createMovementComponent(100.f);
	
}

/*       CONSTRUCTORS/DESTRUCTORS      */

Player::Player(float x, float y) {
	this->initVariables();
	this->initTextureSheet();

	this->setPosition(x, y);

	this->initComponents();
}

Player::~Player() {

}

/*				FUNCTION               */

// Update
void Player::updateTexture() {
	if (this->movementComponent->getState(IDLE)) {
		this->setTexture(*this->textureSheet["IDLE"]);
	} 
	else if (this->movementComponent->getState(MOVING_TOP)) {
		this->setTexture(*this->textureSheet["MOVING_TOP"]);
	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->setTexture(*this->textureSheet["MOVING_DOWN"]);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->setTexture(*this->textureSheet["MOVING_RIGHT"]);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->setTexture(*this->textureSheet["MOVING_LEFT"]);
	}
}

void Player::update(const float& dt) {
	this->updateTexture();
	this->movementComponent->update(dt);

	if (hitboxComponent) {
		this->hitboxComponent->update();
	}
	
}

// Render
void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);

	if (hitboxComponent) {
		this->hitboxComponent->render(target);
	}
	
}
