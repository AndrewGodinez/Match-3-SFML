#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum GemType {
	COMMON,
	BOMB,
	OBSTACLE,

	COUNT
};

enum GemColor {
	GREEN,
	ORANGE,
	RED,
	BLUE,
	YELLOW,

	COUNT
};

class ConfigManager {
private:
	std::string texturePaths = "config/textures_path.xml";
public:
	ConfigManager();
	~ConfigManager();
	std::string colorToString();
	std::string typeToString();

};


