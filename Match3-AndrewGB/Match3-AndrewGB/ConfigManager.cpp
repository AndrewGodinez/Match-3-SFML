#include "ConfigManager.h"

ConfigManager::ConfigManager() {
	configFile.setFileName(TEXTURE_PATHS);
	configFile.openIn();
}

ConfigManager::~ConfigManager() {
}

std::string ConfigManager::colorToString(GemColor color) {
	if (color == GREEN) return "GREEN";
	if (color == ORANGE) return "ORANGE";
	if (color == RED) return "RED";
	if (color == BLUE) return "BLUE";
	if (color == YELLOW) return "YELLOW";
	return "";
	
}

std::string ConfigManager::typeToString(GemType type) {
	if (type == COMMON) return "COMMON";
	if (type == BOMB) return "BOMB";
	if (type == OBSTACLE) return "OBSTACLE";
	return "";
}

std::string ConfigManager::getTexturePath(GemType type) {
	return configFile.getTag(typeToString(type));
}

std::string ConfigManager::getTexturePath(GemType type, GemColor color) {
	return configFile.getTag(colorToString(color));
}
