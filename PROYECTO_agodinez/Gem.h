#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

enum class GemType {
	GREEN,
	ORANGE,
	RED,
	BLUE,
	YELLOW,
	COUNT
};

class Gem {
private:

	GemType type;
	const int width = 64;
	const int height = 64;
	Sprite sprite;
	Texture texture;
	Vector2f positionInGrid;
	Vector2f spritePosition;

public:

	Gem();
	Gem(float xPos, float yPos, Vector2f boardOfsset, GemType type);
	~Gem();
	void updateSpritePos(Vector2f boardOfsset);
	void setPosition(float xPos, float yPos, Vector2f boardOffset);
	void setTexture();
	int getWidth();
	int getHeight();
	GemType getType();
	void draw(RenderWindow &window);

};


