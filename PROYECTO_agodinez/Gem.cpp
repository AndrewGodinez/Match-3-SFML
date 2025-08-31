#include "Gem.h"

Gem::Gem() {
	positionInGrid = Vector2f(0, 0);
	type = static_cast<GemType>(0);

}

Gem::Gem(float xPos, float yPos,Vector2f gameBoard, GemType type) {
	positionInGrid = Vector2f(xPos, yPos);
	this->type = type;
	setTexture();
	updateSpritePos(gameBoard);
}

Gem::~Gem() {

}

void Gem::updateSpritePos(Vector2f gameBoard) {
	float x = ((positionInGrid.x * width) + gameBoard.x);
	float y = ((positionInGrid.y * width) + gameBoard.y);
	sprite.setPosition(Vector2f(x,y));
}

void Gem::setPosition(float xPos, float yPos, Vector2f gameBoard) {
	positionInGrid = Vector2f(xPos, yPos);
	updateSpritePos(gameBoard);
}

void Gem::setTexture() {
	
	switch (type) {
	case GemType::GREEN:
		texture.loadFromFile("assets/gem1.png");
		break;
	case GemType::ORANGE:
		texture.loadFromFile("assets/gem2.png");
		break;
	case GemType::RED:
		texture.loadFromFile("assets/gem3.png");
		break;
	case GemType::BLUE:
		texture.loadFromFile("assets/gem4.png");
		break;
	case GemType::YELLOW:
		texture.loadFromFile("assets/gem5.png");
		break;
	default:
		std::cerr << "Gema sin Especificar\n";
		break;
	}

	sprite.setTexture(texture);
}

int Gem::getWidth() {
	return width;
}

int Gem::getHeight() {
	return height;
}

GemType Gem::getType() {
	return type;
}

void Gem::draw(RenderWindow& window) {
	window.draw(sprite);
}


