#include "game.h"
#include <cstdlib>
#include <iostream>

#define CELL_SIZE 15
#define MARGIN 10

using namespace std;

Game::Game(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		cerr << "Game size must be greater than 0." << endl;
		exit(1);
	}
	size = sf::Vector2i(x, y);

	length = 1;
	snake = new sf::Vector2i[length];
	snake[0] = sf::Vector2i(x / 2, y / 2);

	GeneratePowerUp();
}

Game::~Game()
{
	if (snake)
		delete[] snake;
}

void Game::Start()
{
	sf::RenderWindow window(
		sf::VideoMode(
			size.x * CELL_SIZE + 4 * MARGIN,
			size.y * CELL_SIZE + 4 * MARGIN
		),
		"Snake game"
	);

	MainGameLoop(window);
}

void Game::UpdateGame(sf::RenderWindow& window)
{
	sf::Vector2i head = snake[0];

	if (!IsInBounds(head + dir) && !playerChangedDir)
	{
		ChangeAxis();
		if (IsInSnake(head + dir) || !IsInBounds(head + dir))
		{
			dir *= -1;
		}
	}

	head += dir;
	cout << "Head: (" << head.x << ",  " << head.y << ")" << endl;

	if (powerUp == head)
	{
		length++;
		GeneratePowerUp();
	}

	sf::Vector2i* temp = new sf::Vector2i[length];
	temp[0] = head;
	for (size_t i = 1; i < length; i++)
		temp[i] = snake[i - 1];
	delete[] snake;
	snake = temp;
	temp = nullptr;

	if (BitItself() || !IsInBounds(snake[0]))
	{
		GameOver(window);
	}

	playerChangedDir = false;
}

void Game::Render(sf::RenderWindow& window)
{
	// SMFL
	DrawFrame(window);

	for (size_t i = 0; i < length; i++)
	{
		sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		cell.setFillColor(sf::Color::Black);
		cell.setPosition(sf::Vector2f(snake[i].x * CELL_SIZE + 2 * MARGIN, snake[i].y * CELL_SIZE + 2 * MARGIN));
		window.draw(cell);
	}

	float r = CELL_SIZE / 3.;
	sf::CircleShape apple(r);
	apple.setFillColor(sf::Color::Red);
	apple.setOrigin(sf::Vector2f(r, r));
	apple.setPosition(sf::Vector2f((powerUp.x + 0.5) * CELL_SIZE + 2 * MARGIN, (powerUp.y + 0.5) * CELL_SIZE + 2 * MARGIN));
	window.draw(apple);
}

sf::Vector2i Game::GetDir()
{
	return dir;
}

void Game::SetDir(sf::Vector2i dir)
{
	if ((abs(dir.x) + abs(dir.y)) == 1 && this->dir != -dir)
	{
		this->dir = dir;
		playerChangedDir = true;
	}
}

void Game::GeneratePowerUp()
{
	powerUp = sf::Vector2i(rand() % size.x, rand() % size.y);

	if (IsInSnake(powerUp))
		GeneratePowerUp();

	cout << "Powerup: (" << powerUp.x << ", " << powerUp.y << ")" << endl;
}

bool Game::BitItself()
{
	for (size_t i = 1; i < length; i++)
		if (snake[0] == snake[i])
			return true;
	return false;
}

bool Game::IsInSnake(sf::Vector2i p)
{
	for (size_t i = 0; i < length; i++)
		if (snake[i] == p)
			return true;
	return false;
}

bool Game::IsInBounds(sf::Vector2i p)
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

void Game::DrawFrame(sf::RenderWindow& window)
{
	// Horizontal outer
	sf::RectangleShape line(sf::Vector2f(size.x * CELL_SIZE + 2 * MARGIN, MARGIN / 4.));
	line.setFillColor(sf::Color::Black);
	line.setPosition(sf::Vector2f(MARGIN, MARGIN));
	window.draw(line);

	line.setPosition(sf::Vector2f(MARGIN, size.y * CELL_SIZE + 2.75 * MARGIN));
	window.draw(line);

	// Horizontal inner
	line.setSize(sf::Vector2f(size.x * CELL_SIZE + 0.5 * MARGIN, MARGIN / 4.));
	line.setPosition(sf::Vector2f(1.75 * MARGIN, 1.75 * MARGIN));
	window.draw(line);

	line.setPosition(sf::Vector2f(1.75 * MARGIN, size.y * CELL_SIZE + 2 * MARGIN));
	window.draw(line);

	// Vertical outer
	line.setSize(sf::Vector2f(MARGIN / 4., size.y * CELL_SIZE + 2 * MARGIN));
	line.setPosition(sf::Vector2f(MARGIN, MARGIN));
	window.draw(line);

	line.setPosition(sf::Vector2f(size.x * CELL_SIZE + 2.75 * MARGIN, MARGIN));
	window.draw(line);

	// Vertical inner
	line.setSize(sf::Vector2f(MARGIN / 4., size.y * CELL_SIZE + 0.5 * MARGIN));
	line.setPosition(sf::Vector2f(1.75 * MARGIN, 1.75 * MARGIN));
	window.draw(line);

	line.setPosition(sf::Vector2f(size.x * CELL_SIZE + 2 * MARGIN, 1.75 * MARGIN));
	window.draw(line);
}

void Game::GameOver(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.display();
	}
}

void Game::MainGameLoop(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		Render(window);
		window.display();

		sf::sleep(sf::seconds(0.7 / GetLength()));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.scancode == sf::Keyboard::Scancode::Up
					|| event.key.scancode == sf::Keyboard::Scancode::W)
					SetDir(DIR_UP);
				else if (event.key.scancode == sf::Keyboard::Scancode::Right
					|| event.key.scancode == sf::Keyboard::Scancode::D)
					SetDir(DIR_RIGHT);
				else if (event.key.scancode == sf::Keyboard::Scancode::Down
					|| event.key.scancode == sf::Keyboard::Scancode::S)
					SetDir(DIR_DOWN);
				else if (event.key.scancode == sf::Keyboard::Scancode::Left
					|| event.key.scancode == sf::Keyboard::Scancode::A)
					SetDir(DIR_LEFT);
				else if (event.key.scancode == sf::Keyboard::Scancode::Escape)
					GameOver(window);
			}
		}

		UpdateGame(window);
	}
}
