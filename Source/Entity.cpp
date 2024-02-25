#include "stdafx.h"
#include "Entity.h"

/*         INITIALIZE FUNCTION         */

void Entity::initVariables() {
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}


/*       CONSTRUCTORS/DESTRUCTORS      */

Entity::Entity() {
	this->initVariables();
}

Entity::~Entity() {
	delete this->hitboxComponent;
	delete this->movementComponent;
}

/*				ACCESSORS               */

const sf::Vector2f& Entity::getPosition() const {
	if (this->hitboxComponent) {
		return this->hitboxComponent->getPosition();
	}
	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const {
	if (this->hitboxComponent) {
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const {
	if (this->hitboxComponent && this->movementComponent) {
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const float Entity::getHitboxComponentWidth() const {
	return this->hitboxComponent->getWidth();
}

const float Entity::getHitboxComponentHeight() const {
	return this->hitboxComponent->getHeight();
}

/*				MODIFIERS               */

void Entity::setPosition(float x, float y) {
	if (this->hitboxComponent) {
		this->hitboxComponent->setPosition(x, y);
	}
	else {
		this->sprite.setPosition(x, y);
		this->sprite.setPosition(x, y);
	}
	
}

void Entity::setTexture(sf::Texture& texture) {
	this->sprite.setTexture(texture);
}

/*				COMPONENTS               */

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) {
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float movementSpeed) {
	this->movementComponent = new MovementComponent(this->sprite, movementSpeed);
}

/*				 FUNCTION                */

void Entity::move(const float directionX, const float directionY, const float& dt) {
	if (this->movementComponent) {
		this->movementComponent->move(directionX, directionY, dt);
	}
}

// Update
void Entity::update(const float& dt) {

}


// Render
void render(sf::RenderTarget& target) {

}

