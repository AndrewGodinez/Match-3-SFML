#pragma once
#include "Board.h"
#include "Button.h"

enum GameState {
	MAIN_MENU,
	GAME,
	GAME_OVER,
	GAME_WIN,
	LEVELS
};

class Game {
private:
	bool areItemsLoaded;
	int selectedLevel;
	int beatedLevels;
	TxtFile scoreFile;
	TxtFile saveFile;
	int highScore;
	int lastScore;
	GameState view;
	Board* gameBoard;
	sf::Music* mainSong;
	sf::Font* font;
	sf::RenderWindow *window;
	sf::Clock clock;
public:
	Game();
	~Game();
	void init();
	void callNewBoard();
	void viewsHandler();
	void mainMenuView();
	void levelMenuView();
	void mainGameView();
	void gameOverView();
};

