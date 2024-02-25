#include "stdafx.h"
#include "HitboxComponent.h"

/*       CONSTRUCTORS/DESTRUCTORS      */

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height)
	: sprite(sprite)
 {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->width = width;
	this->height = height;

	this->nextPosition.left = 0;
	this->nextPosition.top = 0;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
	this->hitbox.setSize(sf::Vector2f(this->width, this->height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent() {

}

/*				ACCESSORS              */

const sf::Vector2f& HitboxComponent::getPosition() {
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const {
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity) {
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

const float& HitboxComponent::getWidth() const {
	return this->width;
}

const float& HitboxComponent::getHeight() const {
	return this->height;
}

/*				MODIFIERS              */

void HitboxComponent::setPosition(const sf::Vector2f& position) {
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y) {
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

/*				FUNCTION               */

bool HitboxComponent::intersect(const sf::FloatRect& frect) {
	return this->hitbox.getGlobalBounds().intersects(frect);
}

// Update
void HitboxComponent::update() {
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

// Render
void HitboxComponent::render(sf::RenderTarget& target) {
	target.draw(this->hitbox);
}
