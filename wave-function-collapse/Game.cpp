#include "Game.h"

Game::Game(int width, int height, int fps, const std::string& title, int cell)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	cellsize = cell;
	this->width = width / cell;
	this->height = height / cell;
	finished = false;
	sprites = {};
	sprites.LoadSprites();

	float weight = 1.0f / sprites.images.size();

	
	std::map < std::string, float> res;
	for (const auto t : sprites.images) {
		res[t] = weight;
	}
	model = WFModel(this->width, this->height, res, sprites);

	SetTargetFPS(fps);
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
		const std::string s = grid[i];
		const std::pair pos = Util::ToPos(i, width, height);
		const int x = pos.first;
		const int y = pos.second;
		if(!s.empty()) 
		{
			DrawTexture(sprites.LookupTexture(s),x, y, WHITE);
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
		grid = model.FinishedGridS();
	}
}