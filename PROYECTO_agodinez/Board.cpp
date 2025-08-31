#include "Board.h"

Board::Board() {

	srand(static_cast<unsigned>(time(nullptr)));
	score = 0;
	movesLeft = 0;
	cellSize = 0;
	gameBoard->setPosition(Vector2f(144.f, 44.f));
	initializeBoard();

}

Board::~Board() {

    delete gameBoard;

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLUMNS; j++) {

			delete grid[i][j];

		}

	}

}

void Board::initializeBoard() {

    for (int i = 0; i < ROWS; i++) {

        for (int j = 0; j < COLUMNS; j++) {

            GemType type = static_cast<GemType>(rand() % 5); 

            bool valid = false;

            while (!valid) {

                valid = true;

                if (j >= 2) {
                    if (grid[i][j - 1]->getType() == type &&
                        grid[i][j - 2]->getType() == type) {

                        valid = false;
                        type = static_cast<GemType>(rand() % 5);

                    }

                }

                if (i >= 2) {

                    if (grid[i - 1][j]->getType() == type &&
                        grid[i - 2][j]->getType() == type) {

                        valid = false;
                        type = static_cast<GemType>(rand() % 5);
                    }

                }

            }

            grid[i][j] = new Gem(i,j,gameBoard->getPosition(),type);

        }

    }

    checkMatches();
}

bool Board::isAdjecent(int x1, int y1, int x2, int y2) {

    GemType type = grid[x1][y1]->getType();

    if (y2 - 1 >= 0 && y2 + 1 < COLUMNS) {
        if (grid[x2][y2 - 1]->getType() == type && grid[x2][y2 + 1]->getType() == type) {
            return true;
        }
    }

    if (y2 + 2 < COLUMNS) {
        if (grid[x2][y2 + 1]->getType() == type && grid[x2][y2 + 2]->getType() == type) {
            return true;
        }
    }

    if (y2 - 2 >= 0) {
        if (grid[x2][y2 - 1]->getType() == type && grid[x2][y2 - 2]->getType() == type) {
            return true;
        }
    }


    if (x2 - 1 >= 0 && x2 + 1 < ROWS) {
        if (grid[x2 - 1][y2]->getType() == type && grid[x2 + 1][y2]->getType() == type) {
            return true;
        }
    }
    if (x2 + 2 < ROWS) {
        if (grid[x2 + 1][y2]->getType() == type && grid[x2 + 2][y2]->getType() == type) {
            return true;
        }
    }
    if (x2 - 2 >= 0) {
        if (grid[x2 - 1][y2]->getType() == type && grid[x2 - 2][y2]->getType() == type) {
            return true;
        }
    }

    return false;

}

void Board::checkMatches() {
    
    for (int i = 0; i < ROWS; i++) {

        int count = 1;

        for (int j = 0; j < COLUMNS - 1; j++) {

            if (grid[i][j]->getType() == grid[i][j + 1]->getType()) {

                count++;

                if (count >= 3 && (j + 1 == COLUMNS - 1 || grid[i][j + 1]->getType() != grid[i][j + 2]->getType())) {

                    for (int k = j + 1 - count + 1; k <= j + 1; k++) {

                        std::cout << "Match horizontal en: (" << i << "," << k << ")\n";
                        toDelete[i][k] = true;

                    }

                    count = 1; 
                }

            }

            else {

                count = 1;
            }

        }

    }


    for (int j = 0; j < COLUMNS; j++) {

        int count = 1;

        for (int i = 0; i < ROWS - 1; i++) {

            if (grid[i][j]->getType() == grid[i + 1][j]->getType()) {

                count++;

                if (count >= 3 && (i + 1 == ROWS - 1 || grid[i + 1][j]->getType() != grid[i + 2][j]->getType())) {

                    for (int k = i + 1 - count + 1; k <= i + 1; k++) {

                        std::cout << "Match vertical en: (" << k << "," << j << ")\n";
                        toDelete[k][j] = true;

                    }

                    count = 1;
                }

            }

            else {

                count = 1;
            }

        }

    }

}

void Board::applyGravity() {
   
}

void Board::draw(RenderWindow &window) {

	window.draw(*gameBoard);

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLUMNS; j++) {

			grid[i][j]->draw(window);

		}

	}

}
