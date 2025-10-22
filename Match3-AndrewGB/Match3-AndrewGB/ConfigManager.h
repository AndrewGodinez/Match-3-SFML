#pragma once
#include "File.h"

#define TEXTURE_PATHS "config/textures_path.xml"

enum GemType {
	COMMON,
	BOMB,
	OBSTACLE,
	SIZE
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
	XmlFile configFile;
public:
	ConfigManager();
	~ConfigManager();
	std::string colorToString(GemColor color);
	std::string typeToString(GemType type);
	std::string getTexturePath(GemType type);
	std::string getTexturePath(GemType type, GemColor color);
};


