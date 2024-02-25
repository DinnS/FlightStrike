#include "stdafx.h"
#include "AttributeComponent.h"

/*       CONSTRUCTORS/DESTRUCTORS      */

AttributeComponent::AttributeComponent(int level) {
	// Leveling
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	// Stats
	this->heatlhMax = 100;
	this->damage = 10;
	this->armor = 0;

	this->updateLevel();
	this->resetHealth(true);
}

AttributeComponent::~AttributeComponent() {

}

/*				FUNCTION               */

std::string AttributeComponent::debugPrint() const {
	std::stringstream ss;

	ss << "Level: " << this->level << "\n" <<
		"Exp: " << this->exp << "\n" <<
		"ExpNext: " << this->expNext << "\n" <<
		"Attributes point: " << this->attributePoints << "\n";

	return ss.str();
}

void AttributeComponent::gainExp(const int exp) {
	this->exp += exp;

	this->updateLevel();
}

void AttributeComponent::resetHealth(const bool reset) {
	if (reset) {
		this->health = this->heatlhMax;
	}
}

// Update

void AttributeComponent::updateLevel() {
	while (this->exp >= this->expNext) {
		this->level++;
		this->exp -= this->expNext;

		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		this->attributePoints++;
	}
}

void AttributeComponent::update() {

}
