#include "Button.h"

Button::Button() {
	buttonSprite = new sf::Sprite();
	texture = new sf::Texture();
	if (!texture->loadFromFile("assets/button.png")) std::cerr << "ERROR Trying to load: assets/button.png\n";
	else texture->loadFromFile("assets/button.png");
	position = (sf::Vector2f(static_cast<float>(0), static_cast<float>(0)));
	buttonSprite->setPosition(position);
	font = new sf::Font();
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	buttonText = new sf::Text{"Lorem Ipsum",*font };
	buttonText->setPosition(position.x + 16, position.y + 16);
}

Button::~Button() {
	delete buttonSprite;
	delete texture;
	delete font;
	delete buttonText;
}

Button::Button(int xPos, int yPos, std::string text) {
	buttonSprite = new sf::Sprite();
	texture = new sf::Texture();
	if (!texture->loadFromFile("assets/button.png")) std::cerr << "ERROR Trying to load: assets/button.png\n";
	else texture->loadFromFile("assets/button.png");
	position = (sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)));
	buttonSprite->setPosition(position);
	font = new sf::Font();
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	buttonText = new sf::Text{text,*font};
	buttonText->setPosition(position.x + 60 , position.y  + 40);
	buttonSprite->setTexture(*texture);
	buttonSprite->setOrigin(150.f, 64.f);
	buttonText->setOrigin(150.f, 64.f);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(*buttonSprite);
	window.draw(*buttonText);
}

bool Button::isMouseInsideButton(sf::Vector2i& mousePos) {
	float left = buttonSprite->getPosition().x - 150.f;
	float top = buttonSprite->getPosition().y - 64.f;
	float right = buttonSprite->getPosition().x + texture->getSize().x - 150.f;
	float bottom = buttonSprite->getPosition().y + texture->getSize().y - 64.f;

	return (mousePos.x >= left && mousePos.x < right && mousePos.y >= top && mousePos.y < bottom);
}

void Button::setTextureIndicator(sf::Vector2i& mousePos) {
	if (isMouseInsideButton(mousePos)) {
		buttonSprite->setColor(sf::Color(128, 128, 128, 255));
		buttonText->setFillColor(sf::Color(128, 128, 128, 255));
	}
	else {
		buttonSprite->setColor(sf::Color(255, 255, 255, 255));
		buttonText->setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void Button::setPosition(int xPos, int yPos){
	position = (sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)));
	buttonSprite->setPosition(position);
	buttonText->setPosition(position.x + 60, position.y + 40);
}

void Button::setText(std::string text) {
	buttonText->setString(text);
}
