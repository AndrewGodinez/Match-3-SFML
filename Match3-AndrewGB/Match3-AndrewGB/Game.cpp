#include "Game.h"

Game::Game() {
	gameBoard = nullptr;
	highScore = 0;
	lastScore = 0;
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
	view = MAIN_MENU;
	if (!mainSong->openFromFile("assets/song1.ogg")) std::cerr << "ERROR Trying to load: assets/song1.ogg\n";
	else mainSong->openFromFile("assets/song1.ogg");
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	playButton = new Button(0, 0, "Play");
	backButton = new Button(0, 0, "Back");
	viewsHandler();
}

void Game::callNewBoard() {
	if (gameBoard) delete gameBoard;
	gameBoard = new Board();
	clock.restart();
}

void Game::viewsHandler() {
	mainSong->setLoop(true);
	mainSong->play();
	while (window->isOpen()) {
		if (view == MAIN_MENU) mainMenuView();
		if (view == GAME) mainGameView();
		if (view == GAME_OVER) gameOverView();
		window->clear();
	}
}

void Game::mainMenuView() {
	while (view == MAIN_MENU && window->isOpen()) {
		sf::Event event;
		sf::Text HightScoreText;
		sf::Text madeBy;
		HightScoreText.setFont(*font);
		HightScoreText.setPosition(16, 0);
		HightScoreText.setString("High Score:" + std::to_string(highScore));
		madeBy.setFont(*font);
		madeBy.setPosition(16, 560);
		madeBy.setString("Match-3 Fantasy: Made by zMinds 2025");
		playButton->setText("Start");
		playButton->setPosition(400, 192);
		backButton->setText("Quit");
		backButton->setPosition(400, 384);
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			playButton->setTextureIndicator(mousePos);
			backButton->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (playButton->isMouseInsideButton(mousePos)) {
					callNewBoard();
					view = GAME;
				}
				if (backButton->isMouseInsideButton(mousePos)) {
					window->close();
				}
			}
		}
			window->clear(sf::Color(29, 41, 81));
			window->draw(HightScoreText);
			window->draw(madeBy);
			playButton->draw(*window);
			backButton->draw(*window);
			window->display();
	}
}

void Game::mainGameView() {
	while (view == GAME && window->isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
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

		if (gameBoard) {
			gameBoard->update(deltaTime);
		}

		window->clear(sf::Color(29, 41, 81));
		gameBoard->draw(*window);
		window->draw(score);
		window->draw(moves);
		window->display();
	}
}

void Game::gameOverView() {
	while (view == GAME_OVER && window->isOpen()) {
		sf::Event event;
		sf::Text lastScoreText;
		lastScoreText.setFont(*font);
		lastScoreText.setPosition(16, 0);
		lastScoreText.setString("Your score Score:" + std::to_string(lastScore));
		sf::Text HightScoreText;
		HightScoreText.setFont(*font);
		HightScoreText.setPosition(16, 32);
		HightScoreText.setString("High Score:" + std::to_string(highScore));
		playButton->setText("Start");
		playButton->setPosition(400, 192);
		backButton->setText("Return to Menu");
		backButton->setPosition(400, 384);
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			playButton->setTextureIndicator(mousePos);
			backButton->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (playButton->isMouseInsideButton(mousePos)) {
					callNewBoard();
					view = GAME;
				}
				if (backButton->isMouseInsideButton(mousePos)) {
					view = MAIN_MENU;
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		window->draw(lastScoreText);
		window->draw(HightScoreText);
		playButton->draw(*window);
		backButton->draw(*window);
		window->display();
	}
}
