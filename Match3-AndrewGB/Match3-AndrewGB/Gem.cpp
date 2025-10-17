#include "Gem.h"

Gem::Gem() {
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

void Gem::loadTexture(std::string &texture) {
	try {
		if (!this->texture.loadFromFile(texture)) {
			throw 1;
		}
	}
	catch (int error) {
		if (error == -1) {
			std::cerr << "Fallo al cargar textura en gema\n";
			exit(error);
		}
	}
	sprite.setTexture(this->texture);
}

void Gem::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

GemType Gem::getType(){
	return type;
}
