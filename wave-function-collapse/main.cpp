#include <iostream>
#include <raylib.h>
#include "Game.h"
#include <fstream>
#include <nlohmann/json.hpp>

int main() {
	constexpr int SCREEN_WIDTH = 640;
	constexpr int SCREEN_HEIGHT = 640;
	constexpr int FPS = 60;
	constexpr int CELLSIZE = 16;
	Game game{ SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "Game Window", CELLSIZE };

	while (!Game::should_close()) {
		game.tick();
	}

	return 0;
}