#pragma once
#include "ConfigManager.h"
#include <SFML/Graphics.hpp>

#define WIDTH 64
#define HEIGHT 64

class Gem {
protected:
	GemType type;
	sf::Sprite  sprite;
	sf::Texture texture;
	sf::Vector2f gridPosition;
public:
	Gem();
	~Gem();
	void update(float deltaTime);
	void spritePosition(sf::Vector2f gridOffset);
	void updatePosition(int xPos, int yPos, sf::Vector2f gridOffset);
	virtual void setTexture() = 0;
	void loadTexture(std::string& texture);
	void draw(sf::RenderWindow &window);
	GemType getType();
};

class CommonGem : public Gem {
private:
	GemColor color;
public:
	CommonGem();
	CommonGem(int xPos, int yPos, GemColor color, sf::Vector2f gridOffset);
};