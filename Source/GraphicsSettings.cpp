#include "stdafx.h"
#include "GraphicsSettings.h"

/*       CONSTRUCTORS/DESTRUCTORS      */
GraphicsSettings::GraphicsSettings() {
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->vSync = false;
	this->frameRateLimit = 144;
	this->contextSettings.antialiasingLevel = 0;

}

GraphicsSettings::~GraphicsSettings() {
	
}

/*				FUNCTION               */

void GraphicsSettings::saveToFile(std::string path) {
	std::ofstream ofs(path);

	if (ofs.is_open()) {
		ofs << "// Resolution width" << std::endl;
		ofs << this->resolution.width;
		ofs << std::endl;

		ofs << "// Resolution height" << std::endl;
		ofs << this->resolution.height;
		ofs << std::endl;

		ofs << "// Fullscreen" << std::endl;
		ofs << this->fullscreen;
		ofs << std::endl;

		ofs << "// VSync" << std::endl;
		ofs << this->vSync;
		ofs << std::endl;

		ofs << "// Frame rate limit" << std::endl;
		ofs << this->frameRateLimit;
		ofs << std::endl;

		ofs << "// Antialiasing level" << std::endl;
		ofs << this->contextSettings.antialiasingLevel;
		ofs << std::endl;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(std::string path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		std::string line;
		while (std::getline(ifs, line)) {
			// Parse 
			if (line.find("// Resolution width") == 0)
				ifs >> this->resolution.width;
			else if (line.find("// Resolution height") == 0)
				ifs >> this->resolution.height;
			else if (line.find("// Fullscreen") == 0)
				ifs >> this->fullscreen;
			else if (line.find("// vSync") == 0) 
				ifs >> this->vSync;
			else if (line.find("// Frame rate limit") == 0)
				ifs >> this->frameRateLimit;
			else if (line.find("// Antialiasing level") == 0)
				ifs >> this->contextSettings.antialiasingLevel;
		}	
	}

	ifs.close();
}