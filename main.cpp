#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake game");
	Game game(20, 20);
	game.Render(window);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		game.UpdateGame();
		game.Render(window);
		window.display();
	}
}