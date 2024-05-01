#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

#ifndef __DIRECTIONS__
#define __DIRECTIONS__

#define DIR_UP		sf::Vector2i(0, -1)
#define DIR_RIGHT	sf::Vector2i(1, 0)
#define DIR_DOWN	sf::Vector2i(0, 1)
#define DIR_LEFT	sf::Vector2i(-1, 0)

#endif // !__DIRECTIONS__

#define CELL_SIZE 15
#define MARGIN 10

class Game
{
public:
	Game(int x, int y);
	~Game();

	void Start();

private:
	sf::Vector2i* snake;
	size_t length;

	sf::Vector2i dir;
	sf::Vector2i lastDir;

	sf::Vector2i size;

	sf::Vector2i powerUp;

	void Reset();

	void MainGameLoop(sf::RenderWindow& window);
	void UpdateGame(sf::RenderWindow& window);
	void GeneratePowerUp();

	void DrawFrame(sf::RenderWindow& window);
	void Render(sf::RenderWindow&);
	void GameOver(sf::RenderWindow& window);

	void SetDir(sf::Vector2i dir);
	void ChangeAxis();

	bool BitItself();
	bool IsInSnake(sf::Vector2i p);
	bool IsInBounds(sf::Vector2i p);
};