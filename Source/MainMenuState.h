#pragma once
#include "GameState.h"
#include "GUI.h"

class GameState;
class GUI; 

class MainMenuState : public State
{
private:
	/*                VARIABLES            */
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	
	std::map<std::string, gui::Button*> buttons;

	/*             INITIALIZATION          */
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	/*				FUNCTION               */
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float &dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

