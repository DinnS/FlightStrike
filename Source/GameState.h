#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "Player.h"

class State;
class PauseMenu;
class Player;

class GameState : public State
{
private:
	/*                VARIABLES            */

	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pauseMenu;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	Player* player;
	sf::Vector2f movementDirection;

	/*             INITIALIZATION          */
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initSpritesheet();
	void initPauseMenu();
	void initPlayer();
	void initMap();

public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	GameState(StateData* state_data);
	virtual ~GameState();

	/*				FUNCTION               */

	// Update
	void updateView();
	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);
	void updatePauseMenuButtons();
	void update(const float &dt);

	// Render
	void renderMap(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);
};

