#pragma once
#include "Board.h"

enum GameState {
	MAIN_MENU,
	GAME,
	GAME_OVER,
};

class Game {
private:
	int highScore;
	int lastScore;
	GameState view;
	Board* gameBoard;
	sf::Music* mainSong;
	sf::Font* font;
	sf::RenderWindow *window;
public:
	Game();
	~Game();
	void init();
	void viewsHandler();
	void mainMenuView(sf::Event &event);
	void mainGameView(sf::Event& event);
	void gameOverView(sf::Event& event);
};

