#include "game.h"
#include <cstdlib>

using namespace std;

Game::Game(size_t x, size_t y)
{
	size.x = x;
	size.y = y;

	length = 1;
	snake = new Point[length];
	snake[0].x = x / 2;
	snake[0].y = y / 2;

	GeneratePowerUp();
}

void Game::UpdateGame()
{
	// Trzeba uwzglednic wyjscie poza granice mapy
	Point head = snake[0];
	head.x += dir.x;
	head.y += dir.y;

	if (powerUp == head)
	{
		length++;
		GeneratePowerUp();
	}

	Point* temp = new Point[length];
	temp[0] = head;
	for (size_t i = 1; i < length; i++)
		temp[i] = snake[i - 1];
	delete[] snake;
	snake = temp;
	temp = nullptr;

	if (BitItself())
	{
		// Koniec gry
	}
}

void Game::GeneratePowerUp()
{
	powerUp.x = rand() % size.x;
	powerUp.y = rand() % size.y;

	if (IsInSnake(powerUp))
		GeneratePowerUp();
}

bool Game::BitItself()
{
	for (size_t i = 1; i < length; i++)
		if (snake[0] == snake[i])
			return true;
	return false;
}

bool Game::IsInSnake(Point p)
{
	for (size_t i = 0; i < length; i++)
		if (snake[i] == p)
			return true;
	return false;
}

bool operator==(const Point& A, const Point& B)
{
	return (A.x == B.x && A.y == B.y);
}
