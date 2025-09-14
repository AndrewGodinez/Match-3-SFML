#include "Gem.h"

Gem::Gem() {
	gridPosition = sf::Vector2f(0, 0);
	type = GREEN;
}

Gem::Gem(int xPos, int yPos, sf::Vector2f gridOffset, GemType type) {
	gridPosition = sf::Vector2f(xPos, yPos);
	this->type = type;
	loadTexture();
	spritePosition(gridOffset);
}

Gem::~Gem() {
}

void Gem::spritePosition(sf::Vector2f gridOffset) {
	float xPos = (gridPosition.x * WIDTH) + gridOffset.x;
	float yPos = (gridPosition.y * HEIGHT) + gridOffset.y;
	sprite.setPosition(xPos, yPos);
}

void Gem::updatePosition(int xPos, int yPos, sf::Vector2f gridOffset) {
	gridPosition = sf::Vector2f(xPos,yPos);
	spritePosition(gridOffset);
}

void Gem::loadTexture() {
	if (type == GREEN) {
		if (checkTextures(texturePaths[static_cast<int>(type)])) {
			texture.loadFromFile(texturePaths[static_cast<int>(type)]);
		} else {
			texture.loadFromImage(createReplacementTexture());
		}
	}
	if (type == ORANGE) {
		if (checkTextures(texturePaths[static_cast<int>(type)])) {
			texture.loadFromFile(texturePaths[static_cast<int>(type)]);
		}
		else {
			texture.loadFromImage(createReplacementTexture());
		}
	}
	if (type == RED) {
		if (checkTextures(texturePaths[static_cast<int>(type)])) {
			texture.loadFromFile(texturePaths[static_cast<int>(type)]);
		}
		else {
			texture.loadFromImage(createReplacementTexture());
		}
	}
	if (type == BLUE) {
		if (checkTextures(texturePaths[static_cast<int>(type)])) {
			texture.loadFromFile(texturePaths[static_cast<int>(type)]);
		}
		else {
			texture.loadFromImage(createReplacementTexture());
		}
	}
	if (type == YELLOW) {
		if (checkTextures(texturePaths[static_cast<int>(type)])) {
			texture.loadFromFile(texturePaths[static_cast<int>(type)]);
		}
		else {
			texture.loadFromImage(createReplacementTexture());
		}
	}
	sprite.setTexture(texture);
}

void Gem::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

bool Gem::checkTextures(std::string texture) {
	sf::Texture temp;
	if (!temp.loadFromFile(texture)) {
		std::cerr << "Error: Failed loading texture: " << texture << "\n";
		return false;
	}
	return true;
}

sf::Image Gem::createReplacementTexture() {
	sf::Image img;
	img.create(WIDTH, HEIGHT, sf::Color::Red); 
	return img;
}

GemType Gem::getType(){
	return type;
}
