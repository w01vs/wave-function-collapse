#include "Game.h"

Game::Game(int width, int height, int fps, const std::string& title, int cell)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	cellsize = cell;
	this->width = width / cell;
	this->height = height / cell;
	finished = false;
	map[TileType::BEACH] = {
		{ {UP, {"YELLOW", "YELLOW", "YELLOW"}}, {RIGHT, {"YELLOW", "YELLOW", "YELLOW"} }, {DOWN, {"YELLOW", "YELLOW", "YELLOW"}}, {LEFT, {"YELLOW", "YELLOW", "YELLOW"}} }
	};
	map[TileType::GRASS] = {
		{ {UP, {"GREEN", "GREEN", "GREEN"}}, {RIGHT, {"GREEN", "GREEN", "GREEN"} }, {DOWN, {"GREEN", "GREEN", "GREEN"}}, {LEFT, {"GREEN", "GREEN", "GREEN"}} }
	};
	map[TileType::WATER] = {
		{ {UP, {"BLUE", "BLUE", "BLUE"}}, {RIGHT, {"BLUE", "BLUE", "BLUE"} }, {DOWN, {"BLUE", "BLUE", "BLUE"}}, {LEFT, {"BLUE", "BLUE", "BLUE"}} }
	};

	weights[TileType::BEACH] = 1.0f / 3.0f;
	weights[TileType::GRASS] = 1.0f / 3.0f;
	weights[TileType::WATER] = 1.0f / 3.0f;
	model = WFModel(this->width, this->height, weights, map);

	SetTargetFPS(fps);

	SpriteManager sp;
	sp.LoadSprites();
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseWindow();
}

bool Game::GameShouldClose()
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::Draw() const
{
	ClearBackground(RAYWHITE);
	for (int i = 0; i < height * width; ++i)
	{
		const Tile tile = grid[i];
		const std::pair pos = Util::ToPos(i, width, height);
		const int x = pos.first;
		const int y = pos.second;
		switch (tile.type)
		{
		case TileType::GRASS: DrawRectangle(x * cellsize, y * cellsize, cellsize, cellsize, GREEN); break;
		case TileType::WATER: DrawRectangle(x * cellsize, y * cellsize, cellsize, cellsize, BLUE); break;
		case TileType::BEACH: DrawRectangle(x * cellsize, y * cellsize, cellsize, cellsize, Color{ 232, 221, 146, 255 }); break;
		default: break;
		}
	}
}

void Game::Update()
{
	if(!model.FullyCollapsed())
	{
		grid = model.Iterate();
	}
	else
	{
		if(!finished)
		{
			grid = model.FinishedGrid();
		}
	}
}