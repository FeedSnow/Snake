#include "game.h"
#include <fstream>
#include <sstream>

// ##############################
// #                            #
// #            INIT            #
// #                            #
// ##############################

Game::Game(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		cerr << "Game size must be greater than 0." << endl;
		exit(1);
	}
	size = sf::Vector2i(x, y);
	dir = lastDir = sf::Vector2i(0, 0);

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

void Game::Reset()
{
	length = 1;
	if (snake)
		delete[] snake;
	snake = new sf::Vector2i[length];
	snake[0] = sf::Vector2i(size.x / 2, size.y / 2);

	GeneratePowerUp();
}



// ##############################
// #                            #
// #            GAME            #
// #                            #
// ##############################

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

void Game::MainGameLoop(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		Render(window);
		window.display();

		sf::sleep(sf::seconds(1. / (length + 2)));

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

void Game::UpdateGame(sf::RenderWindow& window)
{
	sf::Vector2i head = snake[0];

	if (!IsInBounds(head + dir))
	{
		ChangeAxis();
		if (IsInSnake(head + dir) || !IsInBounds(head + dir))
		{
			dir *= -1;
		}
	}

	head += dir;

	if (powerUp == head)
	{
		length++;

		if (length == size.x * size.y)
			GameOver(window);

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

	lastDir = dir;
}

void Game::GeneratePowerUp()
{
	powerUp = sf::Vector2i(rand() % size.x, rand() % size.y);

	if (IsInSnake(powerUp))
		GeneratePowerUp();
}



// #########################
// #                       #
// #        DISPLAY        #
// #                       #
// #########################

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

void Game::Render(sf::RenderWindow& window)
{
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

void Game::GameOver(sf::RenderWindow& window)
{
	unsigned int i = 0;

	sf::Font font;
	font.loadFromFile("Lato-Regular.ttf");

	sf::Text gameover("GAME OVER", font);
	gameover.setOrigin
	(
		sf::Vector2f
		(
			gameover.getGlobalBounds().width / 2.,
			gameover.getGlobalBounds().height / 2.
		)
	);
	gameover.setPosition(sf::Vector2f(window.getSize().x / 2., window.getSize().y / 2. - 60));
	gameover.setFillColor(sf::Color::Black);

	stringstream ss;

	ss << "Score: " << length << endl;

	size_t hiscore = 0;
	ifstream hs("hiscore.txt");
	if (hs)
	{
		hs >> hiscore;
		hs.close();
	}
	if (length > hiscore)
		hiscore = length;

	ss << "High score: " << hiscore;

	sf::Text score(ss.str(), font);
	score.setCharacterSize(20);
	score.setOrigin
	(
		sf::Vector2f
		(
			score.getGlobalBounds().width / 2.,
			score.getGlobalBounds().height / 2.
		)
	);
	score.setPosition(sf::Vector2f(window.getSize().x / 2., window.getSize().y / 2.));
	score.setFillColor(sf::Color::Black);

	sf::Text playAgain("Press any key to play again.", font);
	playAgain.setCharacterSize(15);
	playAgain.setOrigin
	(
		sf::Vector2f
		(
			playAgain.getGlobalBounds().width / 2.,
			playAgain.getGlobalBounds().height / 2.
		)
	);
	playAgain.setPosition(sf::Vector2f(window.getSize().x / 2., window.getSize().y / 2. + 60));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				ofstream hs("hiscore.txt");
				if (hs)
					hs << hiscore;
				Reset();
				return;
			}
		}

		playAgain.setFillColor(sf::Color(0, 0, 0, (cos(0.001 * i) + 1) * 128));

		window.clear(sf::Color::White);
		DrawFrame(window);
		window.draw(gameover);
		window.draw(score);
		window.draw(playAgain);
		window.display();

		i++;
	}
}



// ###########################
// #                         #
// #        DIRECTION        #
// #                         #
// ###########################

void Game::SetDir(sf::Vector2i dir)
{
	if ((abs(dir.x) + abs(dir.y)) == 1 && lastDir != -dir)
		this->dir = dir;
}

void Game::ChangeAxis()
{
	dir.x ^= dir.y;
	dir.y ^= dir.x;
	dir.x ^= dir.y;
}



// ##########################
// #                        #
// #        BOOLEANS        #
// #                        #
// ##########################

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