#pragma once
#include <SFML/Audio.hpp>
#include "Gem.h"

class Board {
private:
	static const int GRID_WIDTH = 8;
	static const int GRID_HEIGHT = 8;
	const int GEM_SIZE = 64;
	Gem* grid[GRID_WIDTH][GRID_WIDTH];
	bool toDeleteOnGrid[GRID_WIDTH][GRID_HEIGHT];
	sf::Clock clock;
	sf::RectangleShape* gridShape = new sf::RectangleShape(sf::Vector2f(static_cast<float>(GEM_SIZE * 8), static_cast<float>(GEM_SIZE * 8)));
	sf::RectangleShape* selectionRect = new sf::RectangleShape(sf::Vector2f(GEM_SIZE, GEM_SIZE));
	int selectedX;
	int selectedY;
	int score;
	int movesLeft;
	
public:
	Board();
	~Board();
	void inicializateBoard();
	void checkMatches();
	void destroyMatches();
	void resetDeletedGem();
	void refillBoard();
	void applyGravity();
	void swapGemsPosition(int x1, int y1, int x2, int y2);
	bool checkMatchAtPosition(int x, int y);
	bool isInsideBoard(const sf::Vector2i& mousePos, int& outRow, int& outCol);
	void handleClick(const sf::Vector2i& mousePos);
	void draw(sf::RenderWindow& window);
	int getScore();
	int getMovesLeft();
	

};

