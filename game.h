#pragma once
#include <SFML/Graphics.hpp>

#ifndef __DIRECTIONS__
#define __DIRECTIONS__

#define DIR_UP		sf::Vector2i(0, -1)
#define DIR_RIGHT	sf::Vector2i(1, 0)
#define DIR_DOWN	sf::Vector2i(0, 1)
#define DIR_LEFT	sf::Vector2i(-1, 0)

#endif // !__DIRECTIONS__

class Game
{
public:
	Game(int x, int y);
	~Game();

	void Start();

	void UpdateGame(sf::RenderWindow& window);
	void Render(sf::RenderWindow&);

	sf::Vector2i GetDir();
	void SetDir(sf::Vector2i dir);

	size_t GetLength() { return length; }
private:
	// Array of snake cells
	sf::Vector2i* snake;
	size_t length;
	sf::Vector2i dir;

	sf::Vector2i size;

	sf::Vector2i powerUp;

	bool playerChangedDir;
	bool stop;

	void GeneratePowerUp();
	bool BitItself();
	bool IsInSnake(sf::Vector2i p);
	bool IsInBounds(sf::Vector2i p);
	void ChangeAxis();
	void DrawFrame(sf::RenderWindow& window);
	void GameOver(sf::RenderWindow& window);
	void MainGameLoop(sf::RenderWindow& window);
};