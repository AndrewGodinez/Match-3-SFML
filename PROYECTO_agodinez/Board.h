#pragma once
#include "Gem.h"

class Board {
private:
	static const int ROWS = 8;
	static const int COLUMNS = 8;
	const int GEM_SIZE = 64;
	RectangleShape *gameBoard = new RectangleShape(Vector2f(static_cast<float>(GEM_SIZE*8), static_cast<float>(GEM_SIZE * 8)));
	Gem *grid[ROWS][COLUMNS];
	bool toDelete[ROWS][COLUMNS];
	int score;
	int movesLeft;
	float cellSize;
	Vector2f position;
	
public:
	Board();
	~Board();
	void initializeBoard();
	//bool swapGems();
	//bool isAdjecent();
	void checkMatches();
	void applyGravity();
	//void update();
	//void decreaceMoves();
	void draw(RenderWindow &window);
	Vector2f gemPositionInterpreter(Gem gem);
};

