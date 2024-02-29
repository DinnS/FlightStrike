#include "stdafx.h"
#include "Player.h"

/*         INITIALIZE FUNCTION         */

void Player::initVariables() {
	
}

void Player::initTextureSheet(sf::Texture* spritesheet) {
	this->sprite.setTexture(*spritesheet, true);

	this->textureSheetRect["IDLE"] = sf::IntRect(0, 0, 192, 192);
	this->textureSheetRect["MOVING_TOP"] = sf::IntRect(192, 0, 192, 192);
	this->textureSheetRect["MOVING_DOWN"] = sf::IntRect(384, 0, 192, 192);
	this->textureSheetRect["MOVING_RIGHT"] = sf::IntRect(576, 0, 192, 192);
	this->textureSheetRect["MOVING_LEFT"] = sf::IntRect(768, 0, 192, 192);

	this->sprite.setTextureRect(this->textureSheetRect["IDLE"]);
}

void Player::initComponents() {
	this->createHitboxComponent(this->sprite, 0.f, 0.f, this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
	this->createMovementComponent(100.f);
}

/*       CONSTRUCTORS/DESTRUCTORS      */

Player::Player(float x, float y, sf::Texture* spritesheet) {
	this->initVariables();

	this->initTextureSheet(spritesheet);

	this->setPosition(x, y);

	this->initComponents();
}

Player::~Player() {

}

/*				FUNCTION               */

// Update
void Player::updateTexture() {
	if (this->movementComponent->getState(IDLE)) {
		this->sprite.setTextureRect(this->textureSheetRect["IDLE"]);
	} 
	else if (this->movementComponent->getState(MOVING_TOP)) {
		this->sprite.setTextureRect(this->textureSheetRect["MOVING_TOP"]);
	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->sprite.setTextureRect(this->textureSheetRect["MOVING_DOWN"]);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->sprite.setTextureRect(this->textureSheetRect["MOVING_RIGHT"]);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->sprite.setTextureRect(this->textureSheetRect["MOVING_LEFT"]);
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
