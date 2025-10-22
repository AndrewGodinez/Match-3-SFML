#pragma once
#include "Board.h"
#include "Button.h"

enum GameState {
	MAIN_MENU,
	GAME,
	GAME_OVER,
};

class Game {
private:
	int highScore;
	int lastScore;
	Button *playButton;
	Button *backButton;
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
	void mainGameView();
	void gameOverView();
};

