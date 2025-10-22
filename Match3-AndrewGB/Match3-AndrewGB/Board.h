#pragma once
#include <SFML/Audio.hpp>
#include "Gem.h"
#include "File.h"

class Board {
private:
	CsvFile levelFile;
	static const int GRID_WIDTH = 8;
	static const int GRID_HEIGHT = 8;
	const float GEM_SIZE = 64.f;
	Gem* grid[GRID_WIDTH][GRID_WIDTH];
	bool toDeleteOnGrid[GRID_WIDTH][GRID_HEIGHT];
	sf::RectangleShape* gridShape = new sf::RectangleShape(sf::Vector2f(GEM_SIZE * 8.f, GEM_SIZE * 8.f));
	sf::RectangleShape* selectionRect = new sf::RectangleShape(sf::Vector2f(GEM_SIZE, GEM_SIZE));
	int selectedX;
	int selectedY;
	int score;
	int movesLeft;
	bool animating = false;
	bool pendingResolve = false;

	// Helpers
	bool hasAnyPossibleMove();
	void reshuffleGems();
	
public:
	Board();
	Board(int level);
	~Board();
	void loadLevel(int id);
	void update(float deltaTime);
	void inicializateBoard();
	void createCommonGem(int j, int i);
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

