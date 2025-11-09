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
	bool fourInMatch[GRID_WIDTH][GRID_HEIGHT];
	sf::RectangleShape* gridShape = new sf::RectangleShape(sf::Vector2f(GEM_SIZE * 8.f, GEM_SIZE * 8.f));
	sf::RectangleShape* selectionRect = new sf::RectangleShape(sf::Vector2f(GEM_SIZE, GEM_SIZE));
	int selectedX;
	int selectedY;
	int score;
	int movesLeft;
	bool animating = false;
	bool pendingResolve = false;
	bool pendingBomb = false;
	int pendingBombX = -1;
	int pendingBombY = -1;
	bool pendingExpl = false;
	int pendingExplX = -1;
	int pendingExplY = -1;
	float pendingDestroyDelay = 0.0f;
	
public:
	Board();
	Board(int level);
	~Board();
	void reshuffleGems();
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
	void handleClick(const sf::Vector2i& mousePos);
	void draw(sf::RenderWindow& window);
	bool checkMatchAtPosition(int x, int y);
	bool isInsideBoard(const sf::Vector2i& mousePos, int& outRow, int& outCol);
	bool hasAnyPossibleMove();
	bool isAnimatingOrResolving() const { return animating || pendingResolve; }
	int getMaxRunLengthAtPosition(int x, int y);
	int getScore();
	int getMovesLeft();
};

