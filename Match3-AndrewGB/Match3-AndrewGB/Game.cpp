#include "Game.h"

Game::Game() {
	highScore = 0;
	lastScore = 0;
	view = GAME;
	mainSong = new sf::Music();
	font = new sf::Font();
	window = new sf::RenderWindow(sf::VideoMode(800,600), "Match-3 Fantasy", sf::Style::Close);
}

Game::~Game() {
	delete gameBoard;
	delete mainSong;
	delete font;
	delete window;
}

void Game::init(){
	gameBoard = new Board();
	if (!mainSong->openFromFile("assets/song1.ogg")) std::cerr << "ERROR Trying to load: assets/song1.ogg\n";
	else mainSong->openFromFile("assets/song1.ogg");
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	viewsHandler();
}

void Game::viewsHandler() {
	mainSong->setLoop(true);
	mainSong->play();
	while (window->isOpen()) {
		sf::Event event;
		if (view == MAIN_MENU) mainMenuView(event);
		if (view == GAME) mainGameView(event);
		if (view == GAME_OVER) gameOverView(event);
		window->clear();
	}
}

void Game::mainMenuView(sf::Event& event) {
	
}

void Game::mainGameView(sf::Event& event) {
	sf::Text score;
	score.setFont(*font);
	score.setPosition(sf::Vector2f(16, 0));
	score.setString("Score:" + std::to_string(gameBoard->getScore()));
	sf::Text moves;
	moves.setFont(*font);
	moves.setPosition(sf::Vector2f(664, 0));
	moves.setString("Moves:" + std::to_string(gameBoard->getMovesLeft()));
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		if (gameBoard->getMovesLeft() > 0) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				gameBoard->handleClick(mousePos);

			}
		}
		else {
			lastScore = gameBoard->getScore();
			if (lastScore > highScore) {
				highScore = lastScore;
			}
			view = GAME_OVER;
		}
	}
	window->clear(sf::Color(29, 41, 81));
	gameBoard->draw(*window);
	window->draw(score);
	window->draw(moves);
	window->display();
}

void Game::gameOverView(sf::Event& event) {
	sf::Text lastScoreText;
	lastScoreText.setFont(*font);
	lastScoreText.setPosition(16,0);
	lastScoreText.setString("Your score Score:" + std::to_string(lastScore));
	sf::Text HightScoreText;
	HightScoreText.setFont(*font);
	HightScoreText.setPosition(16, 32);
	HightScoreText.setString("High Score:" + std::to_string(highScore));
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
	window->clear(sf::Color(29, 41, 81));
	window->draw(lastScoreText);
	window->draw(HightScoreText);
	window->display();
}
