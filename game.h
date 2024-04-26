#pragma once

struct Point
{
	size_t x;
	size_t y;
};

bool operator==(const Point& A, const Point& B);

class Game
{
public:
	Game(size_t x, size_t y);

	void UpdateGame();
	void Render();

	Point GetDir();
	void SetDir();
private:
	// Array of snake cells
	Point* snake;
	size_t length;
	Point dir;

	Point size;

	Point powerUp;

	void GeneratePowerUp();
	bool BitItself();
	bool IsInSnake(Point p);
};