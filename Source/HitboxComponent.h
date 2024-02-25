#pragma once

class HitboxComponent
{
private:
	/*                VARIABLES            */
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	float offsetX;
	float offsetY;
	float width;
	float height;

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */

	HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	/*				ACCESSORS              */

	const sf::Vector2f& getPosition();
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	const float& getWidth() const;
	const float& getHeight() const;

	/*				MODIFIERS              */

	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	/*				FUNCTION               */

	bool intersect(const sf::FloatRect& frect);

	// Update
	void update();

	// Render
	void render(sf::RenderTarget& target);




};

