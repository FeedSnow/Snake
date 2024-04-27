#include "game.h"
#include <cstdlib>
#include <iostream>

#define CELL_SIZE 10

using namespace std;

Game::Game(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		cerr << "Game size must be greater than 0." << endl;
		exit(1);
	}
	size.x = x;
	size.y = y;

	length = 1;
	snake = new Point[length];
	snake[0].x = x / 2;
	snake[0].y = y / 2;

	GeneratePowerUp();
}

Game::~Game()
{
	if (snake)
		delete[] snake;
}

void Game::UpdateGame()
{
	Point head = snake[0];

	if (!IsInBounds(head + dir) && !playerChangedDir)
	{
		ChangeAxis();
		if (IsInSnake(head + dir))
		{
			dir.x *= -1;
			dir.y *= -1;
		}
	}

	head += dir;

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

	playerChangedDir = false;
}

void Game::Render(sf::RenderWindow& window)
{
	// SMFL
	for (size_t i = 0; i < length; i++)
	{
		sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		cell.setPosition(sf::Vector2f(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE));
		window.draw(cell);
	}

	sf::CircleShape apple(CELL_SIZE / 2.);
	window.draw(apple);
}

Point Game::GetDir()
{
	return dir;
}

void Game::SetDir(Point dir)
{
	if ((abs(dir.x) + abs(dir.y)) == 1)
		this->dir = dir;
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

bool Game::IsInBounds(Point p)
{
	return (p.x >= 0
		&& p.x < size.x
		&& p.y >= 0
		&& p.y < size.y);
}

void Game::ChangeAxis()
{
	dir.x ^= dir.y;
	dir.y ^= dir.x;
	dir.x ^= dir.y;
}

bool operator==(const Point& A, const Point& B)
{
	return (A.x == B.x && A.y == B.y);
}

Point operator+(const Point& A, const Point& B)
{
	Point sum;
	sum.x = A.x + B.x;
	sum.y = A.y + B.y;
	return sum;
}

Point& Point::operator+=(const Point& A)
{
	this->x += A.x;
	this->y += A.y;
	return *this;
}
