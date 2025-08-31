#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

void testingArea() {
	RenderWindow window(VideoMode(800, 600), "Testing Area", Style::Close | Style::Default);
	Board* board = new Board();

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();
		board->draw(window);
		window.display();
	}

	
}

int main() {

	testingArea();
	

	//Game game;
	//game.run();

}

