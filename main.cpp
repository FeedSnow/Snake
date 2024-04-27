#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

int main()
{
	srand(time(NULL));

	Game game(20, 20);
	game.Start();
	
}