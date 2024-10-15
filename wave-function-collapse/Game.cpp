#include "Game.h"

Game::Game(int width, int height, int fps, const std::string& title, int cell) : model({width / cell, height / cell}), grid(model.wavefunction.grid_ref())
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	cellsize = cell;
	this->width = width / cell;
	this->height = height / cell;
	SetTargetFPS(fps);
	model.wavefunction.initialise();
	model.check_preset();
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
		ClearBackground(WHITE);
		for(int i = 0; i < grid.size(); i++)
		{
			const auto& tiles = grid.at(i);
			auto pair = Util::from_grid(i, width, height);
			if(tiles.size() == 1)
				DrawTexture(tiles.at(0)->image, pair.first * cellsize, pair.second * cellsize, WHITE);
		}

#ifdef LINES
		for(int i = 0; i < width; i++)
		{
			DrawLine(i * cellsize, 0, i * cellsize, height * cellsize, BLACK);
		}
		for(int i = 0; i < height; i++)
		{
			DrawLine(0, i * cellsize, width * cellsize, i * cellsize, BLACK);
		}
#endif
}

void Game::update()
{
	if(!model.finished)
		model.iterate();
	if(model.impossible)
	{
		model.wavefunction.reset();
		model.impossible = false;
	}
		
}