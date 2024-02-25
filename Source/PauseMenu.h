#pragma once

#include "GUI.h"

class GUI;

class PauseMenu
{
private:
	/*                VARIABLES            */
	sf::Font& font;
	sf::Text pauseMenuText;

	sf::RectangleShape background;
	sf::RectangleShape container;
	
	std::map<std::string, gui::Button*> buttons;
public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	PauseMenu(sf::VideoMode& videoMode, sf::Font& font);
	virtual ~PauseMenu();

	/*				ACCESSORS                */
	std::map<std::string, gui::Button*>& getButtons();

	/*				FUNCTION               */
	const bool isButtonPressed(const std::string key);
	void addButton(
		const std::string key, 
		const float y, 
		const float width, const float height, 
		const unsigned char_size, const std::string text
	);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

