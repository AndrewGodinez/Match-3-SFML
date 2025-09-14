#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::Sprite* buttonSprite;
	sf::Texture* texture;
	sf::Vector2f position;
	sf::Font* font;
	sf::Text* buttonText;
public:
	Button();
	~Button();
	Button(int xPos,int yPos,std::string text);
	void draw(sf::RenderWindow &window);
	bool isMouseInsideButton(sf::Vector2i& mousePos);
	void setTextureIndicator(sf::Vector2i& mousePos);
	void setPosition(int xPos, int yPos);
	void setText(std::string text);

};

