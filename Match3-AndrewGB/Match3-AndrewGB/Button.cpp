#include "Button.h"


Button::Button() {
	buttonBuffer.loadFromFile("assets/button_hover.ogg");
	buttonSound.setBuffer(buttonBuffer);
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

Button::Button(int xPos, int yPos, std::string text, sf::Vector2i size) {
	buttonSprite = new sf::Sprite();
	texture = new sf::Texture();
	if (!texture->loadFromFile("assets/button.new.png")) std::cerr << "ERROR Trying to load: assets/button.png\n";
	else texture->loadFromFile("assets/button.new.png");
	position = (sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)));
	buttonSprite->setPosition(position);
	font = new sf::Font();
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	buttonText = new sf::Text{text,*font};
	buttonSprite->setTexture(*texture);
	this->size = size;
	setSize(size.x, size.y);
}

void Button::centerText() {
	sf::FloatRect textBounds = buttonText->getLocalBounds();
	buttonText->setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	buttonText->setPosition(buttonSprite->getPosition());
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(*buttonSprite);
	window.draw(*buttonText);
}

bool Button::isMouseInsideButton(sf::Vector2i& mousePos) {
	buttonSound.play();
	float left = buttonSprite->getPosition().x - size.x / 2.f;
	float top = buttonSprite->getPosition().y - size.y / 2.f;
	float right = buttonSprite->getPosition().x + size.x / 2.f;
	float bottom = buttonSprite->getPosition().y + size.y / 2.f;
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
	centerText();
}

void Button::setText(std::string text) {
	buttonText->setString(text);
	centerText(); 
}

void Button::setSize(int width, int height) {
	size = sf::Vector2i(width, height);
	buttonSprite->setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	buttonSprite->setScale(static_cast<float>(width) / texture->getSize().x, static_cast<float>(height) / texture->getSize().y);	
	centerText();
}