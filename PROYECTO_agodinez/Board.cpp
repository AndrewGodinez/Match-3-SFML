#include "Board.h"

Board::Board() {
	for (int i = 0; i < ROWS; i++) {
		grid[i] = new Gem[COLS];
	}
}

Board::~Board() {
	delete grid;
}
