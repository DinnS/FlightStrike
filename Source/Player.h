#pragma once
#include "Entity.h"


class Entity;

class Player : public Entity
{
private:
	/*                VARIABLES            */
	std::map<std::string, sf::Texture*> textureSheet;

	/*             INITIALIZATION          */
	void initVariables();
	void initTextureSheet();
	void initComponents();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	Player(float x, float y);
	virtual ~Player();

	/*				FUNCTION               */

	// Update
	void updateTexture();
	void update(const float& dt);

	// Render
	void render(sf::RenderTarget& target);
};

