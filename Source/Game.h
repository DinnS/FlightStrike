#pragma once
#include "MainMenuState.h"

class MainMenuState;

class Game
{
private:
	/*                VARIABLES            */
	// Main sfml stuff
	sf::RenderWindow* window;
	sf::Event sfmlEvent;

	sf::Clock dtClock;
	float dt;
	
	// States manager
	std::stack<State*> states;

	// Sharing info between states
	StateData stateData;

	// Graphics setup
	GraphicsSettings gfxSettings;
	
	// All Used Keys
	std::map<std::string, int> supportedKeys;

	/*             INITIALIZATION          */
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	Game();
	virtual ~Game();

	/*				FUNCTION               */

	// Update
	void updateDt();
	void updateSfmlEvents();
	void update();

	// Render
	void render();

	// Core
	void run();

};

