#include "Game.h"

Game::Game(int width, int height, int fps, const std::string& title, int cell)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	cellsize = cell;
	this->width = width / cell;
	this->height = height / cell;

	SetTargetFPS(fps);
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseWindow();
}

bool Game::should_close()
{
	return WindowShouldClose();
}

void Game::tick()
{
	BeginDrawing();
	update();
	draw();
	EndDrawing();
}

void Game::draw() const
{
	
}

void Game::update()
{

}