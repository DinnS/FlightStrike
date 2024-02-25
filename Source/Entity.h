#pragma once
#include "HitboxComponent.h"
#include "MovementComponent.h"

class HitboxComponent;
class MovementComponent;

class Entity
{
private:
	/*             INITIALIZATION          */
	void initVariables();


protected:
	/*                VARIABLES            */
	sf::Sprite sprite;

	/*                COMPONENTS           */
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;


public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	Entity();
	virtual ~Entity();

	/*				ACCESSORS               */

	virtual const sf::Vector2f& getPosition() const;

	virtual const sf::FloatRect getGlobalBounds() const;

	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	const float getHitboxComponentWidth() const;
	
	const float getHitboxComponentHeight() const;
	
	/*				MODIFIERS               */

	void setPosition(float x, float y);

	void setTexture(sf::Texture& texture);

	/*				COMPONENTS               */

	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

	void createMovementComponent(const float movementSpeed);

	/*				FUNCTION               */

	void move(const float directionX, const float directionY, const float &dt);

	// Update
	virtual void update(const float& dt) = 0;

	// Render
	virtual void render(sf::RenderTarget& target) = 0;
};

