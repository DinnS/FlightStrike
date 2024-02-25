#pragma once

#include "GraphicsSettings.h"

class GraphicsSettings;
class State;

class StateData {
	/*
	*  Class for storing data and exchange between states
	*/
public:
	// Constructors
	StateData() {};

	// Variables
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected:
	/*                VARIABLES            */
	std::stack<State*>* states;
	StateData* stateData;

	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	bool pause;
	bool quit;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	/*             INITIALIZATION          */
	virtual void initKeybinds() = 0;

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	State(StateData* state_data);
	virtual ~State();

	/*				ACCESSORS               */
	const bool& getQuit() const;
	const bool getKeyTime();

	/*				FUNCTION               */
	void pauseState();
	void unpauseState();
	void endState();

	virtual void updateMousePosition(sf::View* view = NULL);
	virtual void updateKeyTime(const float &dt);
	virtual void updateInput(const float &dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;


};

