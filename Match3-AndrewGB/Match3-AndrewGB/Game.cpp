#include "Game.h"

Game::Game() {
	view = MAIN_MENU;
	levelScoreRequirement = 0;
	areItemsLoaded = false;
	beatedLevels = 2;
	selectedLevel = 0;
	gameBoard = nullptr;
	highScore = 0;
	lastScore = 0;
	nameInputBox = nullptr;
	waitingForName = false;
	playerName = "";
	highScoreViewLevel = 1;
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
	if (nameInputBox) delete nameInputBox;
}

void Game::init(){
	if (!mainSong->openFromFile("assets/song1.ogg")) std::cerr << "ERROR: Failed to load music file: assets/song1.ogg\n";
	else mainSong->openFromFile("assets/song1.ogg");
	if (!font->loadFromFile("assets/Ubuntu-Title.ttf")) std::cerr << "ERROR: Failed to load font file: assets/Ubuntu-Title.ttf\n";
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
		if (view == HIGH_SCORES) highScoreView();
		window->clear();
	}
}

void Game::mainMenuView() {
	Button* playButton = new Button(0, 0, "Start", sf::Vector2i(320, 128));
	Button* highScoresButton = new Button(0, 0, "High Scores", sf::Vector2i(320, 128));
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
		playButton->setPosition(400, 150);
		highScoresButton->setPosition(400, 300);
		backButton->setPosition(400, 450);
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			playButton->setTextureIndicator(mousePos);
			highScoresButton->setTextureIndicator(mousePos);
			backButton->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (playButton->isMouseInsideButton(mousePos)) {
					view = LEVELS;
				}
				if (highScoresButton->isMouseInsideButton(mousePos)) {
					highScoreViewLevel = 1;
					view = HIGH_SCORES;
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
			highScoresButton->draw(*window);
			backButton->draw(*window);
			window->display();
	}
	delete playButton;
	delete highScoresButton;
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
					highScoresHandler.loadHighScores(selectedLevel);
					highScore = highScoresHandler.getHighScore();
					callNewBoard();
					view = GAME;
				}
				if (level2Button->isMouseInsideButton(mousePos) && beatedLevels >= 2) {
					levelScoreRequirement = 1000;
					selectedLevel = 2;
					highScoresHandler.loadHighScores(selectedLevel);
					highScore = highScoresHandler.getHighScore();
					callNewBoard();
					view = GAME;
				}
				if (level3Button->isMouseInsideButton(mousePos) && beatedLevels >= 3 ) {
					levelScoreRequirement = 1200;
					selectedLevel = 3;
					highScoresHandler.loadHighScores(selectedLevel);
					highScore = highScoresHandler.getHighScore();
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
		sf::Text highScoreText;
		highScoreText.setFont(*font);
		highScoreText.setPosition(sf::Vector2f(16, 32));
		highScoreText.setString("High Score:" + std::to_string(highScore));
		
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
		window->draw(highScoreText);
		window->draw(moves);
		window->draw(requirement);
		window->display();
	}
	delete backButton;
}

void Game::gameWinView() {
	bool qualifiesForHighScore = false;
	if (highScoresHandler.getScoreCount() < 10 || lastScore > highScoresHandler.getScoreAt(9)) {
		qualifiesForHighScore = true;
		waitingForName = true;
	}
	if (nameInputBox == nullptr && qualifiesForHighScore) {
		nameInputBox = new InputBox(400, 200, 400, 64, 20);
		nameInputBox->setActive(true);
	}
	Button* nextButton = new Button(400, 108, "Next level", sf::Vector2i(320, 128));
	Button* replayButton = new Button(400, 308, "Replay Level", sf::Vector2i(320, 128));
	Button* backButton = new Button(400, 508, "Return to menu", sf::Vector2i(320, 128));
	while (view == GAME_WIN && window->isOpen()) {
		sf::Event event;
		sf::Text lastScoreText;
		lastScoreText.setFont(*font);
		lastScoreText.setPosition(16, 0);
		lastScoreText.setString("Your score:" + std::to_string(lastScore));
		sf::Text highScoreText;
		highScoreText.setFont(*font);
		highScoreText.setPosition(16, 32);
		highScoreText.setString("High Score:" + std::to_string(highScore));
		sf::Text instructionText;
		if (waitingForName && qualifiesForHighScore) {
			instructionText.setFont(*font);
			instructionText.setCharacterSize(20);
			instructionText.setFillColor(sf::Color::Yellow);
			instructionText.setString("New High Score! Enter your name:");
			sf::FloatRect textBounds = instructionText.getLocalBounds();
			instructionText.setOrigin(textBounds.left + textBounds.width / 2.f, 
			                          textBounds.top + textBounds.height / 2.f);
			instructionText.setPosition(400, 120);
		}
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			if (waitingForName && qualifiesForHighScore && nameInputBox) {
				nameInputBox->handleEvent(event, mousePos);
				if (nameInputBox->wasAccepted()) {
					playerName = nameInputBox->getInputString();
					if (!playerName.empty()) {
						highScoresHandler.addNewScore(lastScore, playerName);
						highScoresHandler.saveHighScores(selectedLevel);
						highScore = highScoresHandler.getHighScore();
						delete nameInputBox;
						nameInputBox = nullptr;
						waitingForName = false;
					}
				}
			}
			else {
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
							if (beatedLevels < selectedLevel + 1) {
								beatedLevels = selectedLevel + 1;
								saveFile.setFileName("save.ini");
								saveFile.openOut();
								saveFile.replaceContent(std::to_string(beatedLevels));
							}
							selectedLevel++;
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
							highScoresHandler.loadHighScores(selectedLevel);
							highScore = highScoresHandler.getHighScore();
							callNewBoard();
							view = GAME;
						}
					}
					if (backButton->isMouseInsideButton(mousePos)) {
						if (beatedLevels < selectedLevel + 1) {
							beatedLevels = selectedLevel + 1;
							saveFile.setFileName("save.ini");
							saveFile.openOut();
							saveFile.replaceContent(std::to_string(beatedLevels));
						}
						view = MAIN_MENU;
					}
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		window->draw(lastScoreText);
		window->draw(highScoreText);
		if (waitingForName && qualifiesForHighScore && nameInputBox) {
			window->draw(instructionText);
			nameInputBox->draw(*window);
		}
		else {
			nextButton->draw(*window);
			replayButton->draw(*window);
			backButton->draw(*window);
		}
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
	highScoresHandler.loadHighScores(highScoreViewLevel);
	Button* level1Button = new Button(150, 548, "Level 1", sf::Vector2i(160, 48));
	Button* level2Button = new Button(400, 548, "Level 2", sf::Vector2i(160, 48));
	Button* level3Button = new Button(650, 548, "Level 3", sf::Vector2i(160, 48));
	Button* backButton = new Button(64, 32, "Back", sf::Vector2i(64, 64));
	while (view == HIGH_SCORES && window->isOpen()) {
		sf::Event event;
		sf::Text titleText;
		titleText.setFont(*font);
		titleText.setCharacterSize(32);
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setString("HIGH SCORES - LEVEL " + std::to_string(highScoreViewLevel));
		sf::FloatRect titleBounds = titleText.getLocalBounds();
		titleText.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
		titleText.setPosition(400, 40);
		sf::Text rankHeader;
		rankHeader.setFont(*font);
		rankHeader.setCharacterSize(20);
		rankHeader.setFillColor(sf::Color::Cyan);
		rankHeader.setString("Rank");
		rankHeader.setPosition(100, 80);
		sf::Text nameHeader;
		nameHeader.setFont(*font);
		nameHeader.setCharacterSize(20);
		nameHeader.setFillColor(sf::Color::Cyan);
		nameHeader.setString("Name");
		nameHeader.setPosition(250, 80);
		sf::Text scoreHeader;
		scoreHeader.setFont(*font);
		scoreHeader.setCharacterSize(20);
		scoreHeader.setFillColor(sf::Color::Cyan);
		scoreHeader.setString("Score");
		scoreHeader.setPosition(550, 80);
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			backButton->setTextureIndicator(mousePos);
			level1Button->setTextureIndicator(mousePos);
			level2Button->setTextureIndicator(mousePos);
			level3Button->setTextureIndicator(mousePos);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (backButton->isMouseInsideButton(mousePos)) {
					view = MAIN_MENU;
				}
				if (level1Button->isMouseInsideButton(mousePos)) {
					highScoreViewLevel = 1;
					highScoresHandler.loadHighScores(highScoreViewLevel);
				}
				if (level2Button->isMouseInsideButton(mousePos)) {
					highScoreViewLevel = 2;
					highScoresHandler.loadHighScores(highScoreViewLevel);
				}
				if (level3Button->isMouseInsideButton(mousePos)) {
					highScoreViewLevel = 3;
					highScoresHandler.loadHighScores(highScoreViewLevel);
				}
			}
		}
		window->clear(sf::Color(29, 41, 81));
		window->draw(titleText);
		window->draw(rankHeader);
		window->draw(nameHeader);
		window->draw(scoreHeader);
		int scoreCount = highScoresHandler.getScoreCount();
		for (int i = 0; i < 10; i++) {
			float yPosition = 120.f + (i * 40.f);
			sf::Text rankText;
			rankText.setFont(*font);
			rankText.setCharacterSize(18);
			rankText.setPosition(100, yPosition);
			if (i % 2 == 0) {
				rankText.setFillColor(sf::Color::White);
			} else {
				rankText.setFillColor(sf::Color(200, 200, 200, 255));
			}
			std::string rankStr = "#" + std::to_string(i + 1);
			rankText.setString(rankStr);
			sf::Text nameText;
			nameText.setFont(*font);
			nameText.setCharacterSize(18);
			nameText.setPosition(250, yPosition);
			nameText.setFillColor(rankText.getFillColor());
			sf::Text scoreText;
			scoreText.setFont(*font);
			scoreText.setCharacterSize(18);
			scoreText.setPosition(550, yPosition);
			scoreText.setFillColor(rankText.getFillColor());
			if (i < scoreCount) {
				std::string playerName = highScoresHandler.getPlayerNameAt(i);
				int score = highScoresHandler.getScoreAt(i);
				if (playerName.empty()) {
					playerName = "Anon";
				}
				nameText.setString(playerName);
				scoreText.setString(std::to_string(score));
				if (i == 0) {
					rankText.setFillColor(sf::Color(255, 215, 0, 255));
					nameText.setFillColor(sf::Color(255, 215, 0, 255));
					scoreText.setFillColor(sf::Color(255, 215, 0, 255));
				} else if (i == 1) {
					rankText.setFillColor(sf::Color(192, 192, 192, 255));
					nameText.setFillColor(sf::Color(192, 192, 192, 255));
					scoreText.setFillColor(sf::Color(192, 192, 192, 255));
				} else if (i == 2) {
					rankText.setFillColor(sf::Color(205, 127, 50, 255));
					nameText.setFillColor(sf::Color(205, 127, 50, 255));
					scoreText.setFillColor(sf::Color(205, 127, 50, 255));
				}
			} else {
				nameText.setString("---");
				scoreText.setString("---");
				nameText.setFillColor(sf::Color(80, 80, 80, 255));
				scoreText.setFillColor(sf::Color(80, 80, 80, 255));
			}
			window->draw(rankText);
			window->draw(nameText);
			window->draw(scoreText);
		}
		level1Button->draw(*window);
		level2Button->draw(*window);
		level3Button->draw(*window);
		backButton->draw(*window);
		window->display();
	}
	delete level1Button;
	delete level2Button;
	delete level3Button;
	delete backButton;
}