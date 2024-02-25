#pragma once

enum movement_states {
	IDLE = 0,
	MOVING,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_TOP,
	MOVING_DOWN
};

class MovementComponent
{
private:
	/*                VARIABLES            */
	sf::Sprite& sprite;

	float movementSpeed;

	sf::Vector2f velocity;

	short unsigned int lastState;

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	MovementComponent(sf::Sprite& sprite, float movementSpeed);
	virtual ~MovementComponent();

	/*				ACCESSORS               */
	const float& getMovementSpeed() const;
	const sf::Vector2f& getVelocity() const;

	const bool getState(const short unsigned int state);
	const short unsigned int getLastState();

	/*				FUNCTION               */
	void stopVelocity(bool stopLeft = true, bool stopRight = true, bool stopTop = true, bool stopBottom = true);

	void move(const float directionX, const float directionY, const float& dt);
	void update(const float& dt);
};

