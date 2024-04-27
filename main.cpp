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
			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.scancode == sf::Keyboard::Scancode::Up
					|| event.key.scancode == sf::Keyboard::Scancode::W)
					game.SetDir(DIR_UP);
				else if (event.key.scancode == sf::Keyboard::Scancode::Right
					|| event.key.scancode == sf::Keyboard::Scancode::D)
					game.SetDir(DIR_RIGHT);
				else if (event.key.scancode == sf::Keyboard::Scancode::Down
					|| event.key.scancode == sf::Keyboard::Scancode::S)
					game.SetDir(DIR_DOWN);
				else if (event.key.scancode == sf::Keyboard::Scancode::Left
					|| event.key.scancode == sf::Keyboard::Scancode::A)
					game.SetDir(DIR_LEFT);
			}
		}

		window.clear(sf::Color::White);
		//game.DrawFrame(window);
		game.UpdateGame();
		game.Render(window);
		window.display();

		sf::sleep(sf::seconds(0.7 / game.GetLength()));
	}
}