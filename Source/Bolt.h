#pragma once
#include "HitboxComponent.h"

class Bolt
{
private:
	/*                VARIABLES            */

	sf::Sprite bolt;
	sf::Texture boltTexture;

	/*                COMPONENTS           */

	HitboxComponent* hitboxComponent;

	/*             INITIALIZATION          */

	void initVariables();
	void initComponents();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	Bolt(float x, float y);
	virtual ~Bolt();

	/*				ACCESSORS              */


	/*				MODIFIERS              */

	void setPosition(float x, float y);

	/*				FUNCTION               */

	// Update
	void update();

	// Render
	void render(sf::RenderTarget& target);






};

