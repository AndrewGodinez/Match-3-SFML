#include "Gem.h"

Gem::Gem() {
}

Gem::~Gem() {
}

void Gem::update(float deltaTime) {
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

void Gem::setType(GemType type) {
	this->type = type;
}

void Gem::setGridPosition(sf::Vector2f position) {
	gridPosition = position;
}

GemType Gem::getType(){
	return type;
}

CommonGem::CommonGem() {
}

CommonGem::CommonGem(int xPos, int yPos, GemColor color, sf::Vector2f gridOffset) {
	this->color = color;
	gridPosition = sf::Vector2f(xPos, yPos);
	spritePosition(gridOffset);
	setType(GemType::COMMON);
	setTexture();
}

void CommonGem::setTexture() {
	std::string texturePath = configManager.getTexturePath(GemType::COMMON, color);
	try {
		if (!texture.loadFromFile(texturePath))
			{
			throw - 1;
		}
	}
	catch (int e) {
		if (e == -1) {
			std::cerr << "Fallo al cargar textura de gema comun.\n" << "Programa Terminado\n";
			exit(e);
		}
	}
	std::cout << texturePath << " Textura cargada\n";
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}
