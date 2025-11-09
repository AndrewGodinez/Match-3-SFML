#include "Gem.h"
#include <cmath>

Gem::Gem() {
}

Gem::~Gem() {
}

void Gem::update(float deltaTime) {
	if (moving) {
		sf::Vector2f pos = sprite.getPosition();
		sf::Vector2f dir = targetPixelPos - pos;
		float len2 = dir.x * dir.x + dir.y * dir.y;
		if (len2 < 1.0f) {
			sprite.setPosition(targetPixelPos);
			moving = false;
			return;
		}
		float len = std::sqrt(len2);
		sf::Vector2f norm(dir.x / len, dir.y / len);
		float stepLen = moveSpeed * deltaTime;
		sf::Vector2f step(norm.x * stepLen, norm.y * stepLen);
		if ((step.x * step.x + step.y * step.y) >= len2) {
			sprite.setPosition(targetPixelPos);
			moving = false;
		} else {
			sprite.setPosition(sf::Vector2f(pos.x + step.x, pos.y + step.y));
		}
	}
}

void Gem::spritePosition(sf::Vector2f gridOffset) {
	float xPos = (gridPosition.x * WIDTH) + gridOffset.x;
	float yPos = (gridPosition.y * HEIGHT) + gridOffset.y;
	if (!moving) sprite.setPosition(xPos, yPos);
}

void Gem::updatePosition(int xPos, int yPos, sf::Vector2f gridOffset) {
	gridPosition = sf::Vector2f(xPos,yPos);
	// Set animation target in pixels
	targetPixelPos = sf::Vector2f(gridPosition.x * WIDTH + gridOffset.x,
		gridPosition.y * HEIGHT + gridOffset.y);
	moving = true;
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

void Gem::setOpacity(float alpha) {
	sf::Color color = sprite.getColor();
	color.a = static_cast<sf::Uint8>(alpha);
	sprite.setColor(color);
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
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}

GemColor CommonGem::getColor() {
	return color;
}

ObstacleGem::ObstacleGem() {
}

ObstacleGem::ObstacleGem(int xPos, int yPos, sf::Vector2f gridOffset) {
	gridPosition = sf::Vector2f(xPos, yPos);
	spritePosition(gridOffset);
	setType(GemType::OBSTACLE);
	setTexture();
}

void ObstacleGem::setTexture() {
	std::string texturePath = configManager.getTexturePath(GemType::OBSTACLE);
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
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}

BombGem::BombGem() {
}

BombGem::BombGem(int xPos, int yPos, sf::Vector2f gridOffset) {
	gridPosition = sf::Vector2f(xPos, yPos);
	spritePosition(gridOffset);
	setType(GemType::BOMB);
	setTexture();
}

void BombGem::setTexture() {
	std::string texturePath = configManager.getTexturePath(GemType::BOMB);
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
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}
