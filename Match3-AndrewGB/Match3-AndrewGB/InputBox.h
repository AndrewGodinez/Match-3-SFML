#pragma once 
#include <iostream>
#include <string>
#include "Button.h"
#include <SFML/Graphics.hpp>

class InputBox {
private:
    sf::Sprite* boxSprite;
    sf::Texture* texture;
    sf::Font* font;
    sf::Text* displayText;
    sf::Text* placeholderText;
    sf::Vector2f position;
    sf::Vector2i size;
    Button* clearButton;
    Button* acceptButton;
    bool isActive;
    bool isAccepted;
    std::string inputString;
    int maxLength;
    
    void centerText();
public:
    InputBox(float x, float y, float width, float height, int maxLen = 20);
    ~InputBox();
    void handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window);
    std::string getInputString() const;
    void clearInput();
    bool wasAccepted();
    void resetAccepted();
    void setActive(bool active);
    bool getActive() const;
};