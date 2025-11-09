#include "Game.h"
#include "Button.h"

Game::Game() {
	view = MAIN_MENU;
	levelScoreRequirement = 0;
	areItemsLoaded = false;
	beatedLevels = 2;
	selectedLevel = 0;
	gameBoard = nullptr;
	highScore = 0;
	lastScore = 0;
	mainSong = new sf::Music();
	font = new sf::Font();
	window = new sf::RenderWindow(sf::VideoMode(800,600), "Match-3 Fantasy", sf::Style::Close);
	window->setFramerateLimit(60);
	icon.loadFromFile("icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

Game::~Game() {
	delete gameBoard;
	delete mainSong;
	delete font;
	delete window;
}

void Game::init(){
	if (!mainSong->openFromFile("assets/song1.ogg")) std::cerr << "ERROR Trying to load: assets/song1.ogg\n";
	else mainSong->openFromFile("assets/song1.ogg");
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR Trying to load: assets/Ubuntu-Title.ttf\n";
	else font->loadFromFile("assets/Ubuntu-Title.ttf");
	TxtFile runner;
	runner.setFileName("run.ini");
	try {
		if (!runner.openIn()){
			throw -1;
		}
	}
	catch (int e) {
		if (e == -1) {
			std::cerr << "First run detected. Initializing files...\n";
			runner.setFileName("run.ini");
			runner.openOut();
			runner.replaceContent("firstInit = true");
			runner.openIn();
		}
	}
	if (runner.isTextOnFile("firstInit = true")) {
		for (int i = 0; i < 3; i++) {
			scoreFile.setFileName("level" + std::to_string(i + 1) + "HS.ini");
			scoreFile.openOut();
			scoreFile.replaceContent("0");
		}
		saveFile.setFileName("save.ini");
		saveFile.openOut();
		saveFile.replaceContent("0");
		runner.replaceContent("firstInit = false");
	}
	saveFile.setFileName("save.ini");
	saveFile.openIn();
	beatedLevels = stoi(saveFile.getFirstLine());
	viewsHandler();
}

void Game::callNewBoard() {
	if (gameBoard) delete gameBoard;
	gameBoard = new Board(selectedLevel);
	clock.restart();
}

void Game::viewsHandler() {
	mainSong->setLoop(true);
	mainSong->play();
	while (window->isOpen()) {
		if (view == MAIN_MENU) mainMenuView();
		if (view == GAME) mainGameView();
		if (view == GAME_WIN) gameWinView();
		if (view == GAME_OVER) gameOverView();
		if (view == LEVELS) levelMenuView();
		window->clear();
	}
}

void Game::mainMenuView() {
	Button* playButton = new Button(0, 0, "Start", sf::Vector2i(320, 128));
	Button* backButton = new Button(0, 0, "Exit", sf::Vector2i(320, 128));
	while (view == MAIN_MENU && window->isOpen()) {
		sf::Event event;
		sf::Text HightScoreText;
		sf::Text madeBy;
		HightScoreText.setFont(*font);
		HightScoreText.setPosition(16, 0);
		madeBy.setFont(*font);
		madeBy.setPosition(16, 560);
		madeBy.setString("Match-3 Fantasy: Made by Andrew Godinez 2025");
		playButton->setPosition(400, 192);
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
					view = LEVELS;
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
	delete playButton;
	delete backButton;
}

void Game::levelMenuView() {
	Button* level1Button = new Button(400, 108, "Level 1", sf::Vector2i(320, 128));
	Button* level2Button = new Button(400, 308, "Level 2", sf::Vector2i(320, 128));
	Button* level3Button = new Button(400, 508, "Level 3", sf::Vector2i(320, 128));
	Button* backButton = new Button(64, 548, "Back", sf::Vector2i(64, 64));
	
	while (view == LEVELS && window->isOpen()) {
		sf::Text levelsText;
		sf::Event event;
		if (beatedLevels < 2) {
			level2Button->setText("Beat Level 1 to Play");
		}
		else {
			level2Button->setText("Level 2");
		}
		if (beatedLevels < 3) {
			level3Button->setText("Beat Level 2 to Play");
		}
		else {
			level3Button->setText("Level 3");
		}
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			level1Button->setTextureIndicator(mousePos);
			level2Button->setTextureIndicator(mousePos);
			level3Button->setTextureIndicator(mousePos);
			backButton->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (level1Button->isMouseInsideButton(mousePos)) {
					levelScoreRequirement = 800;
					selectedLevel = 1;
					callNewBoard();
					view = GAME;
				}
				if (level2Button->isMouseInsideButton(mousePos) && beatedLevels >= 2) {
					levelScoreRequirement = 1000;
					selectedLevel = 2;
					callNewBoard();
					view = GAME;
				}
				if (level3Button->isMouseInsideButton(mousePos) && beatedLevels >= 3 ) {
					levelScoreRequirement = 1200;
					selectedLevel = 3;
					callNewBoard();
					view = GAME;
				}
				if (backButton->isMouseInsideButton(mousePos)) {
					view = MAIN_MENU;
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		backButton->draw(*window);
		level1Button->draw(*window);
		level2Button->draw(*window);
		level3Button->draw(*window);
		window->display();
	}
	delete level1Button;
	delete level2Button;
	delete level3Button;
	delete backButton;
}

void Game::mainGameView() {
	Button* backButton = new Button(64, 548, "Back", sf::Vector2i(64, 64));
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
		sf::Text requirement;
		requirement.setFont(*font);
		requirement.setPosition(sf::Vector2f(300, 0));
		requirement.setString("Score to beat:" + std::to_string(levelScoreRequirement));
		scoreFile.setFileName("level" + std::to_string(selectedLevel) + "HS.ini");
		scoreFile.openIn();
		highScore = stoi(scoreFile.getFirstLine());
		if (gameBoard) {
			gameBoard->update(deltaTime);
		}
		lastScore = gameBoard->getScore();
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (gameBoard->getMovesLeft() > 0) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
					backButton->setTextureIndicator(mousePos);
					gameBoard->handleClick(mousePos);
					if (backButton->isMouseInsideButton(mousePos)) {
						view = LEVELS;
					}
				}
			}
			else {
				if (!gameBoard->isAnimatingOrResolving()) {
					if (lastScore >= levelScoreRequirement) {
						if (lastScore > highScore) {
							highScore = lastScore;
							scoreFile.setFileName("level" + std::to_string(selectedLevel) + "HS.ini");
							scoreFile.openOut();
							scoreFile.replaceContent(std::to_string(highScore));
						}
						view = GAME_WIN;
					} else {
						view = GAME_OVER;
					}
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		backButton->draw(*window);
		gameBoard->draw(*window);
		window->draw(score);
		window->draw(moves);
		window->draw(requirement);
		window->display();
	}
	delete backButton;
}

void Game::gameWinView() {
	Button* nextButton = new Button(400, 108, "Next level", sf::Vector2i(320, 128));
	Button* replayButton = new Button(400, 308, "Replay Level", sf::Vector2i(320, 128));
	Button* backButton = new Button(400, 508, "Return to menu", sf::Vector2i(320, 128));
	while (view == GAME_WIN && window->isOpen()) {
		sf::Event event;
		sf::Text lastScoreText;
		lastScoreText.setFont(*font);
		lastScoreText.setPosition(16, 0);
		lastScoreText.setString("Your score Score:" + std::to_string(lastScore));
		sf::Text HightScoreText;
		HightScoreText.setFont(*font);
		HightScoreText.setPosition(16, 32);
		scoreFile.setFileName("level" + std::to_string(selectedLevel) + "HS.ini");
		scoreFile.openIn();
		HightScoreText.setString("High Score:" + scoreFile.getFirstLine());
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			nextButton->setTextureIndicator(mousePos);
			replayButton->setTextureIndicator(mousePos);
			backButton->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (replayButton->isMouseInsideButton(mousePos)) {
					callNewBoard();
					view = GAME;
				}
				if (selectedLevel < 3) {
					if (nextButton->isMouseInsideButton(mousePos)) {
						selectedLevel++;
						if (beatedLevels < selectedLevel-1) {
							beatedLevels = selectedLevel;
							saveFile.setFileName("save.ini");
							saveFile.openOut();
							saveFile.replaceContent(std::to_string(beatedLevels));
						}
						switch (selectedLevel) {
						case 1:
							levelScoreRequirement = 800;
							break;
						case 2:
							levelScoreRequirement = 1000;
							break;
						case 3:
							levelScoreRequirement = 1200;
							break;
						}
						callNewBoard();
						view = GAME;
					}
				}
				if (backButton->isMouseInsideButton(mousePos)) {
					selectedLevel++;
					if (beatedLevels < selectedLevel) {
						beatedLevels = selectedLevel;
						saveFile.setFileName("save.ini");
						saveFile.openOut();
						saveFile.replaceContent(std::to_string(beatedLevels));
					}
					view = MAIN_MENU;
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		window->draw(lastScoreText);
		window->draw(HightScoreText);
		nextButton->draw(*window);
		replayButton->draw(*window);
		backButton->draw(*window);
		window->display();
	}
	delete nextButton;
	delete replayButton;
	delete backButton;
}

void Game::gameOverView() {
	Button* playButton = new Button(400, 192, "Replay", sf::Vector2i(320, 128));
	Button* backButton = new Button(400, 384, "Return to Menu", sf::Vector2i(320, 128));
	while (view == GAME_OVER && window->isOpen()) {
		sf::Event event;
		sf::Text lastScoreText;
		lastScoreText.setFont(*font);
		lastScoreText.setPosition(16, 0);
		lastScoreText.setString("Your score Score:" + std::to_string(lastScore));
		sf::Text HightScoreText;
		HightScoreText.setFont(*font);
		HightScoreText.setPosition(16, 32);
		scoreFile.setFileName("level" + std::to_string(selectedLevel) + "HS.ini");
		scoreFile.openIn();
		HightScoreText.setString("High Score:" + scoreFile.getFirstLine());	
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
	delete playButton;
	delete backButton;
}

void Game::highScoreView() {
	while (view == HIGH_SCORES && window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}
		window->clear(sf::Color(29, 41, 81));
		window->display();
	}
}