#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum GemType {
	GREEN,
	ORANGE,
	RED,
	BLUE,
	YELLOW,
	COUNT
};		

class Gem {
private:
	const int WIDTH = 64;
	const int HEIGHT = 64;
	static const int TEXTURE_AMOUNT = static_cast<int>(GemType::COUNT);
	GemType type;
	sf::Sprite  sprite;
	sf::Texture texture;
	sf::Vector2f gridPosition;
	std::string texturePaths[TEXTURE_AMOUNT] = {
	  "assets/gem1.png",
	  "assets/gem2.png",
	  "assets/gem3.png",
	  "assets/gem4.png",
	  "assets/gem5.png"
	};
public:
	Gem();
	Gem(int xPos, int yPos, sf::Vector2f gridOffset, GemType type);
	~Gem();
	void spritePosition(sf::Vector2f gridOffset);
	void updatePosition(int xPos, int yPos, sf::Vector2f gridOffset);
	void loadTexture();
	void draw(sf::RenderWindow &window);
	bool checkTextures(std::string texture);
	sf::Image createReplacemetTexture(); 
};

