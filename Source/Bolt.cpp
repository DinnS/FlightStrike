#include "stdafx.h"
#include "Bolt.h"

/*         INITIALIZE FUNCTION         */

void Bolt::initVariables() {
	this->boltTexture.loadFromFile("Resources/Graphics/Game/bolt.png");
	this->bolt.setTexture(this->boltTexture);
}

void Bolt::initComponents() {
	this->hitboxComponent = new HitboxComponent(this->bolt, 0, 0, this->bolt.getGlobalBounds().width, this->bolt.getGlobalBounds().height);
}


/*       CONSTRUCTORS/DESTRUCTORS      */
Bolt::Bolt(float x, float y) {
	this->initVariables();

	this->setPosition(x, y);

	this->initComponents();
}

Bolt::~Bolt() {
	delete this->hitboxComponent;
}

/*				ACCESSORS              */


/*				MODIFIERS              */

void Bolt::setPosition(float x, float y) {
	this->bolt.setPosition(x, y);
}

/*				FUNCTION               */

// Update
void Bolt::update() {
	this->hitboxComponent->update();
}

// Render
void Bolt::render(sf::RenderTarget& target) {
	target.draw(this->bolt);
	this->hitboxComponent->render(target);
}
