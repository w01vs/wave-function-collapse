#include <iostream>
#include <raylib.h>
#include "Game.h"

int main() {
	const int SCREEN_WIDTH = 400;
	const int SCREEN_HEIGHT = 400;
	const int FPS = 60;
	Game game{ SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "Game Window" };

	while (!game.GameShouldClose()) {
		game.Tick();
	}

	return 0;
}