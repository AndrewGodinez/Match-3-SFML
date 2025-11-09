#pragma once
#include "ConfigManager.h"
#include <SFML/Graphics.hpp>

#define WIDTH 64
#define HEIGHT 64

class Gem {
protected:
	bool animated = false;
	ConfigManager configManager;
	GemType type;
	sf::Sprite  sprite;
	sf::Texture texture;
	sf::Vector2f gridPosition;
	bool moving = false;
	sf::Vector2f targetPixelPos;
	float moveSpeed = 500.f; 
public:
	Gem();
	virtual ~Gem();
	void update(float deltaTime);
	void spritePosition(sf::Vector2f gridOffset);
	void updatePosition(int xPos, int yPos, sf::Vector2f gridOffset);
	virtual void setTexture() = 0;
	void loadTexture(std::string& texture);
	void draw(sf::RenderWindow &window);
	void setType(GemType type);
	void setGridPosition(sf::Vector2f position);
	void setOpacity(float alpha); 
	GemType getType();
	virtual GemColor getColor() = 0;
	bool isMoving() const { return moving; }
};

class CommonGem : public Gem {
private:
	GemColor color;
public:
	CommonGem();
	CommonGem(int xPos, int yPos, GemColor color, sf::Vector2f gridOffset);
	void setTexture() override;
	GemColor getColor() override;
};

class BombGem : public Gem {
public:
	BombGem();
	BombGem(int xPos, int yPos, sf::Vector2f gridOffset);
	void setTexture() override;
	GemColor getColor() override { return GemColor::COUNT; }
};

class ObstacleGem : public Gem {
public:
	ObstacleGem();
	ObstacleGem(int xPos, int yPos, sf::Vector2f gridOffset);
	void setTexture() override;
	GemColor getColor() override { return GemColor::COUNT; }
};