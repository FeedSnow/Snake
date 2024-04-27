#pragma once
#include <SFML/Graphics.hpp>

struct Point
{
	int x;
	int y;

	Point& operator+=(const Point& A);
};

bool operator==(const Point& A, const Point& B);
Point operator+(const Point& A, const Point& B);

class Game
{
public:
	Game(int x, int y);
	~Game();

	void UpdateGame();
	void Render(sf::RenderWindow&);

	Point GetDir();
	void SetDir(Point dir);
private:
	// Array of snake cells
	Point* snake;
	size_t length;
	Point dir;

	Point size;

	Point powerUp;

	bool playerChangedDir;

	void GeneratePowerUp();
	bool BitItself();
	bool IsInSnake(Point p);
	bool IsInBounds(Point p);
	void ChangeAxis();
};