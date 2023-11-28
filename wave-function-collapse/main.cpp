#include <iostream>
#include <raylib.h>
#include "Game.h"

int main() {
	constexpr int SCREEN_WIDTH = 48;
	constexpr int SCREEN_HEIGHT = 48;
	constexpr int FPS = 60;
	Game game{ SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "Game Window", 16 };

	while (!Game::GameShouldClose()) {
		game.Tick();
	}

	return 0;
}