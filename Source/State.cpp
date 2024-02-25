#include "stdafx.h"
#include "State.h"

/*       CONSTRUCTORS/DESTRUCTORS      */

State::State(StateData* state_data) {
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->pause = false;
	this->quit = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 20.f;
}

State::~State() {

}

/*				ACCESSORS               */
	
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}



/*				FUNCTION               */

void State::pauseState() {
	this->pause = true;
}

void State::unpauseState() {
	this->pause = false;
}

void State::endState() {
	this->quit = true;
}


// Update

void State::updateMousePosition(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view) {
		this->window->setView(*view);
	}
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 60.f * dt;
	}
}
