#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(int x, int y);
	~Game();

	void UpdateGame();
	void Render(sf::RenderWindow&);

	sf::Vector2i GetDir();
	void SetDir(sf::Vector2i dir);
private:
	// Array of snake cells
	sf::Vector2i* snake;
	size_t length;
	sf::Vector2i dir;

	sf::Vector2i size;

	sf::Vector2i powerUp;

	bool playerChangedDir;

	void GeneratePowerUp();
	bool BitItself();
	bool IsInSnake(sf::Vector2i p);
	bool IsInBounds(sf::Vector2i p);
	void ChangeAxis();
};