#include "stdafx.h"
#include "MovementComponent.h"

/*       CONSTRUCTORS/DESTRUCTORS      */

MovementComponent::MovementComponent(sf::Sprite& sprite, float movementSpeed) 
	: sprite(sprite)
{
	this->movementSpeed = movementSpeed;
	
}

MovementComponent::~MovementComponent() {

}

/*				ACCESSORS               */
const float& MovementComponent::getMovementSpeed() const {
	return this->movementSpeed;
}

const sf::Vector2f& MovementComponent::getVelocity() const {
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned int state) {
	switch (state) {
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f) {
			this->lastState = state;
			return true;
		}
		break;

	case MOVING:
		if (!this->velocity.x == 0.f || !this->velocity.y == 0.f) {
			return true;
		}
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.f) {
			this->lastState = state;
			return true;
		}
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f) {
			this->lastState = state;
			return true;
		}
		break;

	case MOVING_TOP:
		if (this->velocity.y < 0.f) {
			this->lastState = state;
			return true;
		}
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.f) {
			this->lastState = state;
			return true;
		}
		break;

	}
	return false;
	
	
}

const short unsigned int MovementComponent::getLastState() {
	return lastState;
}

/*				FUNCTION               */

void MovementComponent::stopVelocity(bool stopLeft, bool stopRight, bool stopTop, bool stopBottom) {
	/*  reset velocity to 0  */
	if (stopLeft && this->velocity.x < 0.f) {
		this->velocity.x = 0.f;
	}

	if (stopRight && this->velocity.x > 0.f) {
		this->velocity.x = 0.f;
	}

	if (stopTop && this->velocity.y < 0.f) {
		this->velocity.y = 0.f;
	}

	if (stopBottom && this->velocity.y > 0.f) {
		this->velocity.y = 0.f;
	}
}

void MovementComponent::move(const float directionX, const float directionY, const float& dt) {
	int multiplyMovementSpeed = 10;
	sf::Vector2f direction = sf::Vector2f(directionX, directionY);
	if (direction.x != 0.f || direction.y != 0.f) {
		direction = direction / (std::sqrt(direction.x * direction.x + direction.y * direction.y));
	}

	this->velocity.x = (multiplyMovementSpeed * this->movementSpeed * direction.x) * dt;
	this->velocity.y = (multiplyMovementSpeed * this->movementSpeed * direction.y) * dt;
}

// Update
void MovementComponent::update(const float& dt) {
	this->sprite.move(this->velocity);
}

