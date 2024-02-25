#pragma once

class GraphicsSettings
{
public:
	/*       CONSTRUCTORS/DESTRUCTORS      */
	GraphicsSettings();
	virtual ~GraphicsSettings();

	/*                VARIABLES            */
	sf::VideoMode resolution;
	bool fullscreen;
	bool vSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;

	/*				FUNCTION               */
	void saveToFile(std::string path);
	void loadFromFile(std::string path);
};

