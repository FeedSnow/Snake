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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			game.SetDir(DIR_UP);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			game.SetDir(DIR_RIGHT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			game.SetDir(DIR_DOWN);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			game.SetDir(DIR_LEFT);

		window.clear();
		game.UpdateGame();
		game.Render(window);
		window.display();
	}
}