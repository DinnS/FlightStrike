#include "stdafx.h"
#include "Game.h"

/*         INITIALIZE FUNCTION         */

void Game::initVariables() {
    this->window = nullptr;

    this->dt = 0.f;
}

void Game::initGraphicsSettings(){
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow() {
    // Create SFML window
    if (this->gfxSettings.fullscreen) {
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            "Fevolve",
            sf::Style::Fullscreen,
            this->gfxSettings.contextSettings
        );
    }
    else {
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            "Fevolve",
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings
        );
    }

    // Setup SFML window
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.vSync);
}

void Game::initKeys() {
    // Init all used keys
    std::ifstream ifs("Config/supportedKeys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
    // Debug | Show keys value
    /*for (auto i : this->supportedKeys) {
        std::cout << i.first << " " << i.second << std::endl;
    }*/
    // Find out the key value
    /*std::cout << sf::Keyboard::Key::A;*/
}

void Game::initStateData() {
    // Init data for sharing between states
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
}

void Game::initStates() {
    // First state init
    this->states.push(new MainMenuState(&this->stateData));
}

/*       CONSTRUCTORS/DESTRUCTORS      */

Game::Game(){
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}


/*				FUNCTION               */

// Update
void Game::updateDt() {
    // Updates dt variable to render one frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSfmlEvents() {
    // Check active sfml events
    while (this->window->pollEvent(this->sfmlEvent))
    {
        // Click on the close icon, close the window
        if (this->sfmlEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}


void Game::update() {
    this->updateSfmlEvents();

    // Check if states exist
    if(!this->states.empty()) {
        // Updating current state
        if (this->window->hasFocus()) {
            this->states.top()->update(this->dt);

            // Check state status
            if (this->states.top()->getQuit()) {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else {
        this->window->close();
    }

}

// Render
void Game::render() {
    this->window->clear();
    
    // Render current state
    if (!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

// Core
void Game::run() {
	// Game loop
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}