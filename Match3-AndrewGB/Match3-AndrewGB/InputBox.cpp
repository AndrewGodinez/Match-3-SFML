#include "InputBox.h"


InputBox::InputBox(float x, float y, float width, float height, int maxLen) {
    position = sf::Vector2f(x, y);
    size = sf::Vector2i(static_cast<int>(width), static_cast<int>(height));
    isActive = false;
    isAccepted = false;
    inputString = "";
    maxLength = maxLen;
    boxSprite = new sf::Sprite();
    texture = new sf::Texture();
    if (!texture->loadFromFile("assets/button.new.png")) {
        std::cerr << "ERROR: Failed to load InputBox texture: assets/button.new.png\n";
    } else {
        texture->loadFromFile("assets/button.new.png");
    }
    boxSprite->setTexture(*texture);
    boxSprite->setPosition(position);
    boxSprite->setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
    boxSprite->setScale(static_cast<float>(width) / texture->getSize().x, static_cast<float>(height) / texture->getSize().y);
    font = new sf::Font();
    if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) {
        std::cerr << "ERROR: Failed to load font file: assets/Ubuntu-Title.ttf\n";
    } else {
        font->loadFromFile("assets/Ubuntu-Title.ttf");
    }
    displayText = new sf::Text("", *font, 24);
    displayText->setFillColor(sf::Color::White);
    placeholderText = new sf::Text("Type your name...", *font, 24);
    placeholderText->setFillColor(sf::Color(150, 150, 150, 255));
    centerText();
    float buttonWidth = 128.f;
    float buttonHeight = 48.f;
    float buttonY = y + height / 2.f + buttonHeight + 16.f;
    clearButton = new Button(
        static_cast<int>(x - buttonWidth / 2.f - 8.f), 
        static_cast<int>(buttonY), 
        "Clear", 
        sf::Vector2i(static_cast<int>(buttonWidth), static_cast<int>(buttonHeight))
    );
    acceptButton = new Button(
        static_cast<int>(x + buttonWidth / 2.f + 8.f), 
        static_cast<int>(buttonY), 
        "Accept", 
        sf::Vector2i(static_cast<int>(buttonWidth), static_cast<int>(buttonHeight))
    );
}

InputBox::~InputBox() {
    delete boxSprite;
    delete texture;
    delete font;
    delete displayText;
    delete placeholderText;
    delete clearButton;
    delete acceptButton;
}

void InputBox::centerText() {
    sf::FloatRect textBounds = displayText->getLocalBounds();
    displayText->setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    displayText->setPosition(position);
    
    sf::FloatRect placeholderBounds = placeholderText->getLocalBounds();
    placeholderText->setOrigin(placeholderBounds.left + placeholderBounds.width / 2.f, placeholderBounds.top + placeholderBounds.height / 2.f);
    placeholderText->setPosition(position);
}

void InputBox::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
    // Actualizar indicador visual de botones
    clearButton->setTextureIndicator(const_cast<sf::Vector2i&>(mousePos));
    acceptButton->setTextureIndicator(const_cast<sf::Vector2i&>(mousePos));
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        float left = position.x - size.x / 2.f;
        float top = position.y - size.y / 2.f;
        float right = position.x + size.x / 2.f;
        float bottom = position.y + size.y / 2.f;
        if (mousePos.x >= left && mousePos.x < right && mousePos.y >= top && mousePos.y < bottom) {
            isActive = true;
        } else {
            isActive = false;
        }
        if (clearButton->isMouseInsideButton(const_cast<sf::Vector2i&>(mousePos))) {
            clearInput();
        }
        if (acceptButton->isMouseInsideButton(const_cast<sf::Vector2i&>(mousePos))) {
            if (!inputString.empty()) {
                isAccepted = true;
                isActive = false;
            }
        }
    }
    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {
            if (!inputString.empty()) {
                std::string temp = "";
                for (size_t i = 0; i < inputString.length() - 1; i++) {
                    temp += inputString[i];
                }
                inputString = temp;
                displayText->setString(inputString);
                centerText();
            }
        }
        else if (event.text.unicode == 13) {
            if (!inputString.empty()) {
                isAccepted = true;
                isActive = false;
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            if (static_cast<int>(inputString.length()) < maxLength) {
                inputString += static_cast<char>(event.text.unicode);
                displayText->setString(inputString);
                centerText();
            }
        }
    }
}

void InputBox::draw(sf::RenderWindow& window) {
    if (isActive) {
        boxSprite->setColor(sf::Color(200, 200, 255, 255));
    } else {
        boxSprite->setColor(sf::Color::White);
    }
    window.draw(*boxSprite);
    if (inputString.empty()) {
        window.draw(*placeholderText);
    } else {
        window.draw(*displayText);
    }
    if (isActive) {
        static sf::Clock cursorClock;
        if (static_cast<int>(cursorClock.getElapsedTime().asSeconds() * 2) % 2 == 0) {
            sf::Text cursor("|", *font, 24);
            cursor.setFillColor(sf::Color::White);
            sf::FloatRect textBounds = displayText->getLocalBounds();
            cursor.setPosition(position.x + textBounds.width / 2.f + 5.f, position.y - displayText->getCharacterSize() / 2.f);
            window.draw(cursor);
        }
    }
    clearButton->draw(window);
    acceptButton->draw(window);
}

std::string InputBox::getInputString() const {
    return inputString;
}

void InputBox::clearInput() {
    inputString = "";
    displayText->setString("");
    centerText();
    isAccepted = false;
}

bool InputBox::wasAccepted() {
    return isAccepted;
}

void InputBox::resetAccepted() {
    isAccepted = false;
}

void InputBox::setActive(bool active) {
    isActive = active;
}

bool InputBox::getActive() const {
    return isActive;
}
