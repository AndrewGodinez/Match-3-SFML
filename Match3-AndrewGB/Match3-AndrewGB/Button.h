#pragma once
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button {
private:
	sf::Sprite* buttonSprite;
	sf::Texture* texture;
	sf::Vector2f position;
	sf::Font* font;
	sf::Text* buttonText;
	sf::SoundBuffer buttonBuffer;
	sf::Sound buttonSound;
	sf::Vector2i size; 
public:
	Button();
	~Button();
	Button(int xPos,int yPos,std::string text,sf::Vector2i size);
	void centerText();
	void draw(sf::RenderWindow &window);
	bool isMouseInsideButton(sf::Vector2i& mousePos);
	void setTextureIndicator(sf::Vector2i& mousePos);
	void setPosition(int xPos, int yPos);
	void setText(std::string text);
	void setSize(int width, int height);
};

