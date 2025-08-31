#pragma once
#include<SFML/Graphics.hpp>
#include "Board.h"

using namespace sf;

class Game {
private: 
	RenderWindow window{ VideoMode(800,600), "Match-3 Game", Style::Resize | Style::Close };
	Board board;
	Font font;
public:
	void run();
};

