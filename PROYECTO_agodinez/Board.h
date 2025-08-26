#pragma once
#include "Gem.h"

class Board {
private:

	const int ROWS = 8;
	const int COLS = 8;

	Gem** grid = new Gem* [ROWS];
	
public:
	Board();
	~Board();
};

