#pragma once
#include "Entity.h"


class Entity;

class Player : public Entity
{
private:
	/*                VARIABLES            */
	std::map<std::string, sf::IntRect> textureSheetRect;

	/*             INITIALIZATION          */
	void initVariables();
	void initTextureSheet(sf::Texture* spritesheet);
	void initComponents();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	Player(float x, float y, sf::Texture* spritesheet);
	virtual ~Player();

	/*				FUNCTION               */

	// Update
	void updateTexture();
	void update(const float& dt);

	// Render
	void render(sf::RenderTarget& target);
};

