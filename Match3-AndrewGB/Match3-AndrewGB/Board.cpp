#include "Board.h"

Board::Board() {
	srand(static_cast<unsigned>(time(nullptr)));
	score = 0;
	movesLeft = 20;
	gridShape->setPosition(sf::Vector2f(144.f, 44.f));
	selectedX = -1;
	selectedY = -1;
	selectionRect->setSize(sf::Vector2f(static_cast<float>(GEM_SIZE), static_cast<float>(GEM_SIZE)));
	selectionRect->setFillColor(sf::Color::Transparent);
	selectionRect->setOutlineThickness(3.0f);
	selectionRect->setOutlineColor(sf::Color(255, 255, 255, 100));
	gridShape->setFillColor(sf::Color(0, 0, 0, 100));
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) toDeleteOnGrid[i][j] = false;
	}
	loadLevel(1);
	inicializateBoard();
}

Board::~Board() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			delete grid[i][j];
		}
	}
}
void Board::loadLevel(int id) {
	levelFile.setFileName("levels/level_" + std::to_string(id) + ".csv");
	levelFile.openIn();
}
void Board::update(float deltaTime) {
	bool anyMoving = false;
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (grid[i][j]) {
				grid[i][j]->update(deltaTime);
				if (grid[i][j]->isMoving()) anyMoving = true;
			}
		}
	}
	animating = anyMoving;

	if (!animating && pendingResolve) {
		bool wasFound = true;
		while (wasFound) {
			bool found = false;
			checkMatches();
			for (int i = 0; i < GRID_HEIGHT && !found; i++) {
				for (int j = 0; j < GRID_WIDTH && !found; j++) {
					if (toDeleteOnGrid[i][j]) found = true;
				}
			}
			if (!found) {
				wasFound = false;
				break;
			}
			destroyMatches();
			applyGravity();
			refillBoard();
			anyMoving = false;
			for (int i = 0; i < GRID_HEIGHT; i++) {
				for (int j = 0; j < GRID_WIDTH; j++) {
					if (grid[i][j] && grid[i][j]->isMoving()) anyMoving = true;
				}
			}
			animating = anyMoving;
			if (animating) {
				break;
			}
		}
		if (!animating) pendingResolve = false;
	}
}

void Board::inicializateBoard() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		std::string row = levelFile.getLine(i);
		for (int j = 0; j < GRID_WIDTH; j++) {
			int cell = row[j] - '0';
			if (cell == 0) {
				createCommonGem(j, i);
			} else if (cell == 1) {
				grid[i][j] = new ObstacleGem(j, i, gridShape->getPosition());
			} else {
				createCommonGem(j, i);
			}
		}
	}
}

void Board::createCommonGem(int j, int i) {
	int gemVariety = static_cast<int>(GemColor::COUNT);
	GemColor color = static_cast<GemColor>(rand() % gemVariety);
	bool valid = false;
	while (!valid) {
		valid = true;
		if (j >= 2) {
			if (grid[i][j - 1]->getColor() == color &&
				grid[i][j - 2]->getColor() == color) {
				valid = false;
				color = static_cast<GemColor>(rand() % gemVariety);
			}
		}
		if (i >= 2) {
			if (grid[i - 1][j]->getColor() == color &&
				grid[i - 2][j]->getColor() == color) {
				valid = false;
				color = static_cast<GemColor>(rand() % gemVariety);
			}
		}
	}
	grid[i][j] = new CommonGem(j, i, color, gridShape->getPosition());
}

void Board::checkMatches() {
	resetDeletedGem();
	for (int i = 0; i < GRID_HEIGHT; i++) {
		int count = 1;
		for (int j = 0; j < GRID_WIDTH - 1; j++) {
			if (grid[i][j]->getColor() == grid[i][j + 1]->getColor()) {
				count++;
				if (count >= 3 && (j + 1 == GRID_WIDTH - 1 || grid[i][j + 1]->getColor() != grid[i][j + 2]->getColor())) {
					for (int k = j + 1 - count + 1; k <= j + 1; k++) {
						toDeleteOnGrid[i][k] = true;
					}
					count = 1;
				}
			} else {
				count = 1;
			}
		}
	}
	for (int i = 0; i < GRID_WIDTH; i++) {
		int count = 1;
		for (int j = 0; j < GRID_HEIGHT - 1; j++) {
			if (grid[j][i]->getColor() == grid[j + 1][i]->getColor()) {
				count++;
				if (count >= 3 && (j + 1 == GRID_HEIGHT - 1 || grid[j + 1][i]->getColor() != grid[j + 2][i]->getColor())) {
					for (int k = j + 1 - count + 1; k <= j + 1; k++) {
						toDeleteOnGrid[k][i] = true;
					}
					count = 1;
				} 
			} else {
				count = 1;
			}
		}
	}
}

void Board::destroyMatches() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (toDeleteOnGrid[i][j]) {
				delete grid[i][j];
				grid[i][j] = nullptr;
				toDeleteOnGrid[i][j] = false;
				score += 10;
			}
		}
	}
}

void Board::resetDeletedGem() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			toDeleteOnGrid[i][j] = false;
		}
	}
}

void Board::refillBoard() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (grid[i][j] == nullptr) {
				int gemVariety = static_cast<int>(GemColor::COUNT);
				GemColor type = static_cast<GemColor>(rand() % gemVariety);
				grid[i][j] = new CommonGem(j, i, type, gridShape->getPosition());
			}
		}
	}
}

void Board::applyGravity() {
	for (int x = 0; x < GRID_WIDTH; x++) {
		int writeY = GRID_HEIGHT - 1;
		for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
			Gem* g = grid[y][x];
			if (g == nullptr) continue;
			if (g->getType() == GemType::OBSTACLE) {
				writeY = y - 1;
				continue;
			}
			if (y != writeY) {
				grid[writeY][x] = g;
				grid[y][x] = nullptr;
				grid[writeY][x]->updatePosition(x, writeY, gridShape->getPosition());
			}
			writeY--;
		}
	}
}

void Board::swapGemsPosition(int x1, int y1, int x2, int y2) {
	Gem* temp = grid[y1][x1];
	grid[y1][x1] = grid[y2][x2];
	grid[y2][x2] = temp;
	grid[y1][x1]->updatePosition(x1, y1, gridShape->getPosition());
	grid[y2][x2]->updatePosition(x2, y2, gridShape->getPosition());
}

bool Board::checkMatchAtPosition(int x, int y) {
	if (y < 0 || y >= GRID_HEIGHT || x < 0 || x >= GRID_WIDTH) return false;
	GemColor centerType = grid[y][x]->getColor();
	int count = 1;
	bool loopStopper = false;
	for (int i = x - 1; i >= 0 && loopStopper == false; i--) {
		if (grid[y][i]->getColor() == centerType) count++;
		else loopStopper = true;
	}
	loopStopper = false;
	for (int i = x + 1; i < GRID_WIDTH && loopStopper == false; i++) {
		if (grid[y][i]->getColor() == centerType) count++;
		else loopStopper = true;
	}
	loopStopper = false;
	if (count >= 3) return true;
	count = 1;
	for (int i = y - 1; i >= 0 && loopStopper == false; i--) {
		if (grid[i][x]->getColor() == centerType) count++;
		else loopStopper = true;
	}
	loopStopper = false;
	for (int i = y + 1; i < GRID_HEIGHT && loopStopper == false; i++) {
		if (grid[i][x]->getColor() == centerType) count++;
		else loopStopper = true;
	}
	loopStopper = false;
	if (count >= 3) return true;
	return false;
}

bool Board::isInsideBoard(const sf::Vector2i& mousePos, int& outRow, int& outCol) {
	float left = gridShape->getPosition().x;
	float top = gridShape->getPosition().y;
	float right = gridShape->getPosition().x + GEM_SIZE * GRID_WIDTH;
	float bottom = gridShape->getPosition().y + GEM_SIZE * GRID_HEIGHT;

	if (mousePos.x < left || mousePos.x >= right || mousePos.y < top || mousePos.y >= bottom) return false;

	outCol = (mousePos.x - (int)left) / (int)GEM_SIZE;
	outRow = (mousePos.y - (int)top) / (int)GEM_SIZE;

	if (outRow < 0 || outRow >= GRID_HEIGHT || outCol < 0 || outCol >= GRID_WIDTH) return false;
	return true;
}

void Board::handleClick(const sf::Vector2i& mousePos) {
	int y, x;
	if (!isInsideBoard(mousePos, y, x)) {
		selectedY = -1;
		selectedX = -1;
		return;
	}
	if (animating) return;
	if (selectedY == -1 && selectedX == -1) {
		selectedY = y;
		selectedX = x;
		return;
	}
	if (selectedY == y && selectedX == x) {
		selectedY = -1;
		selectedX = -1;
		return;
	}
	int dr = abs(selectedY - y);
	int dc = abs(selectedX - x);
	if (!((dr == 1 && dc == 0) || (dr == 0 && dc == 1))) {
		selectedY = y;
		selectedX = x;
		return;
	}
	if (grid[selectedY][selectedX]->getType() == GemType::OBSTACLE ||
		grid[y][x]->getType() == GemType::OBSTACLE) {
		selectedY = -1;
		selectedX = -1;
		return;
	}
	swapGemsPosition(selectedX, selectedY, x, y);
	animating = true;
	pendingResolve = true;
	bool match1 = checkMatchAtPosition(selectedX, selectedY);
	bool match2 = checkMatchAtPosition(x,y);
	if (!(match1 || match2)) {
		swapGemsPosition(selectedX, selectedY, x, y);
	} else {
		movesLeft -= 1;
	}
	selectedY = -1;
	selectedX = -1;
}

void Board::draw(sf::RenderWindow& window) {
	window.draw(*gridShape);
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) grid[i][j]->draw(window);
	}
	if (selectedY >= 0 && selectedX >= 0) {
		selectionRect->setPosition(gridShape->getPosition().x + selectedX * GEM_SIZE, gridShape->getPosition().y + selectedY * GEM_SIZE);
		window.draw(*selectionRect);
	}
}

int Board::getScore() {
	return score;
}

int Board::getMovesLeft() {
	return movesLeft;
}

