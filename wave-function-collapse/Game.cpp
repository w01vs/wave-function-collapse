#include "Game.h"

Game::Game(int width, int height, int fps, std::string title)
{
	assert(!GetWindowHandle());
	InitWindow(width, height, title.c_str());
	Init(width, height, 16);
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

std::pair<int, int> Game::ToPos(int gridPos) const
{
	int y = gridPos % height;
	int x = (gridPos - y) / width;
	return { x, y };
}

int Game::ToGridPos(int x, int y) const
{
	return width * x + y;
}

void Game::Draw() const
{
	ClearBackground(RAYWHITE);
	for (int i = 0; i < height * width; ++i)
	{
		const Tile tile = grid[i];
		const std::tuple<int, int> pos = ToPos(i);
		const int x = std::get<0>(pos);
		const int y = std::get<1>(pos);
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
	if (!filled)
	{
		Collapse();
		filled = Util::Filled(grid);
	}
}

void Game::Init(int x, int y, int cell)
{
	filled = false;
	cellsize = cell;
	width = x / cell;
	height = y / cell;
	for (int i = 0; i < height * width; ++i)
	{
		grid.emplace_back(TileType::EMPTY);
	}


	map[TileType::BEACH] = std::vector<Tile>{ TileType::GRASS, TileType::WATER, TileType::BEACH };
	map[TileType::GRASS] = std::vector<Tile>{ TileType::GRASS, TileType::BEACH };
	map[TileType::WATER] = std::vector<Tile>{ TileType::WATER, TileType::BEACH };
	map[TileType::EMPTY] = std::vector<Tile>{ TileType::GRASS, TileType::WATER, TileType::BEACH };
}

void Game::Collapse()
{
	std::vector entropyGrid(height * width, 0);
	std::vector possibleTiles(height * width, std::vector<Tile>{});
	
	GenerateEntropy(entropyGrid, possibleTiles);

	std::vector<int> const indices = Util::LowestAboveZero(entropyGrid);
	if (indices.empty())
	{
		return;
	}


	int const random = Util::RandomInt(0, indices.size() - 1);
	int const index = indices[random];
	Tile result = TileType::EMPTY;
	std::map<Tile, int> tiles;

	std::vector surrounding = { Top(index), Right(index), Bottom(index), Left(index) };

	for (int i : surrounding)
	{
		if (IsOnGrid(i))
		{
			tiles[grid[i]]++;
		}
	}

	int filledAround = 0;
	std::vector<Tile> pt = Util::GetKeys(tiles);
	for (Tile t : pt)
	{
		if(t != TileType::EMPTY)
		{
			filledAround++;
		}
	}

	// divide by 0
	//const auto divider = static_cast<float>(entropyGrid[index] / filledAround);
	// create a map with tile as key, chance (tile count * divider) as value, !!set chance for non-valid tiles to 0!! so you can predefine the chance comparisons.
	// do a random chance for each tile possible
	if (result == TileType::EMPTY)
	{
		const int rand = Util::RandomInt(0, possibleTiles[index].size() - 1);
		result = possibleTiles[index][rand];
	}

	grid[index] = result;
	std::tuple const pos = ToPos(index);
	const int x = std::get<0>(pos);
	const int y = std::get<1>(pos);
	std::cout << x << ", " << y << "- Turned into: " << grid[index] << "\n";
}

void Game::GenerateEntropy(std::vector<int>& entropy, std::vector<std::vector<Tile>>& possibilities) const
{
	
	for (int i = 0; i < height * width; ++i)
	{
		if(grid[i] != TileType::EMPTY)
		{
			possibilities[i] = {};
			continue;
		}
		bool const l = i % width != 0;
		bool const r = (i + 1) % width != 0;
		bool const t = i >= width;
		bool const b = i < (height - 1) * width;
		std::vector<Tile> result = map.at(TileType::EMPTY);

		if (l)
		{
			std::vector<Tile> left = map.at(grid[Left(i)]);
			result = Util::Intersect(result, left);
		}
		if (r)
		{
			std::vector<Tile> right = map.at(grid[Right(i)]);
			result = Util::Intersect(result, right);
		}
		if (t)
		{
			std::vector<Tile> top = map.at(grid[Top(i)]);
			result = Util::Intersect(result, top);
		}

		if (b)
		{
			std::vector<Tile> bottom = map.at(grid[Bottom(i)]);
			result = Util::Intersect(result, bottom);
		}

		if (AdjacentEmpty(i))
		{
			possibilities[i] = result;
			entropy[i] = INT32_MAX;
			continue;
		}

		possibilities[i] = result;

		entropy[i] = possibilities[i].size();
	}
}

bool Game::AdjacentEmpty(int i) const
{
	const std::vector adjacent = { Left(i), Right(i), Top(i), Bottom(i) };
	for (const int n : adjacent)
	{
		if(IsOnGrid(n))
		{
			if (grid[n] != TileType::EMPTY)
			{
				return false;
			}
		}
	}
	return true;
}

int Game::Right(int index) const
{
	return index + 1;
}

int Game::Left(int index) const
{
	return index - 1;
}

int Game::Top(int index) const
{
	return index - width;
}

int Game::Bottom(int index) const
{
	return index + width;
}

int Game::IsOnGrid(int index) const
{
	return index > 0 && index < grid.size();
}
