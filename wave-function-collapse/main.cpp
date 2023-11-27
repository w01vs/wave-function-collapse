#include <iostream>
#include <raylib.h>
#include "Game.h"

int main() {
	constexpr int SCREEN_WIDTH = 400;
	constexpr int SCREEN_HEIGHT = 400;
	constexpr int FPS = 60;
	Game game{ SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "Game Window" };

	while (!Game::GameShouldClose()) {
		game.Tick();
	}

	return 0;
}