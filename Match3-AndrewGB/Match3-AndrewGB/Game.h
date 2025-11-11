#pragma once
#include "Board.h"
#include "Button.h"
#include "HighScoresHandler.h"
#include "InputBox.h"

enum GameState {
	MAIN_MENU,
	GAME,
	GAME_OVER,
	GAME_WIN,
	LEVELS,
	HIGH_SCORES
};

class Game {
private:
	bool areItemsLoaded;
	int selectedLevel;
	int beatedLevels;
	XmlFile scoreFile;
	TxtFile saveFile;
	HighScoresHandler highScoresHandler;
	int highScore;
	int lastScore;
	GameState view;
	Board* gameBoard;
	sf::Music* mainSong;
	sf::Font* font;
	sf::RenderWindow *window;
	sf::Clock clock;
	sf::Image icon;
	int levelScoreRequirement;
	InputBox* nameInputBox;
	bool waitingForName;
	std::string playerName;
	int highScoreViewLevel;
public:
	Game();
	~Game();
	void init();
	void callNewBoard();
	void viewsHandler();
	void mainMenuView();
	void levelMenuView();
	void mainGameView();
	void gameWinView();
	void gameOverView();
	void highScoreView();
};

