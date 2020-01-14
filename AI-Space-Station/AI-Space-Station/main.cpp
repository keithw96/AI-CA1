#include "Game.h"

/// <summary>
/// main entry point
/// </summary>
/// <returns></returns>
int main()
{
	srand(time(NULL));
	Game game;

	game.run();

	return 0;
}