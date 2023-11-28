#include "Game.h"

#include <ranges>

Game::Game(int width, int height, int fps, const std::string& title)
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
		const std::tuple pos = ToPos(i);
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
		grid.emplace_back(TileType::EMPTY);



	map[TileType::BEACH] = {
		{ {UP, {"YELLOW", "YELLOW", "YELLOW"}}, {RIGHT, {"YELLOW", "YELLOW", "YELLOW"} }, {DOWN, {"YELLOW", "YELLOW", "YELLOW"}}, {LEFT, {"YELLOW", "YELLOW", "YELLOW"}} }
	};
	map[TileType::GRASS] = {
		{ {UP, {"GREEN", "GREEN", "GREEN"}}, {RIGHT, {"GREEN", "GREEN", "GREEN"} }, {DOWN, {"GREEN", "GREEN", "GREEN"}}, {LEFT, {"GREEN", "GREEN", "GREEN"}} }
	};
	map[TileType::WATER] = {
		{ {UP, {"BLUE", "BLUE", "BLUE"}}, {RIGHT, {"BLUE", "BLUE", "BLUE"} }, {DOWN, {"BLUE", "BLUE", "BLUE"}}, {LEFT, {"BLUE", "BLUE", "BLUE"}} }
	};
}

void Game::Collapse()
{
	std::vector entropyGrid((int)height * width, 0);
	std::vector possibleTiles((int)height * width, std::vector<Tile>{});
	
	GenerateEntropy(entropyGrid, possibleTiles);

	std::vector<int> const indices = Util::LowestAboveZero(entropyGrid);
	if (indices.empty())
		return;


	int const random = Util::RandomInt(0, (int)indices.size() - 1);
	int const index = indices[random];
	const std::pair pos = ToPos(index);
	std::cout << pos.first << ", " << pos.second << " is now generating" << std::endl;
	Tile result = TileType::EMPTY;
	std::map<Tile, int> tiles;

	const std::vector surrounding = { Util::Top(index, width), Util::Right(index), Util::Bottom(index, width), Util::Left(index) };

	for (const int i : surrounding)
	{
		if (Util::IsOnGrid(i, grid))
			tiles[grid[i]]++;

	}

	int filledAround = 0;
	const std::vector<Tile> keys = Util::GetKeys(tiles);
	for (Tile t : keys)
	{
		if(t != TileType::EMPTY)
			filledAround++;

	}
	std::map<Tile, float> tileChance;
	if(filledAround > 0)
	{
		
		float multipleTiles= 0;
		for(const TileType t : Tile::ALL)
		{
			if(t != TileType::EMPTY)
				multipleTiles += (float)tiles[t];
		}
		const float part = 100 / ((float)possibleTiles[index].size() + multipleTiles);
		for (const Tile t : possibleTiles[index])
		{
			tiles[t]++;
			tileChance[t] = (float)tiles[t] * part;
		}
	}
	
	// do a random chance for each tile possible
	if (!tileChance.empty())
	{
		std::vector<std::pair<Tile, float>> reverse;
		reverse.reserve(tileChance.size());
		for (const std::pair<Tile, float> p : tileChance)
		{
			reverse.emplace_back(p.first, p.second);
		}

		std::sort(reverse.begin(), reverse.end(), [](const auto a, const auto b) {return a.second < b.second; });
		const float rand = Util::RandomFloat(0, 100);
		float totalChance = 0;
		for (const auto pair : reverse)
		{
			const float chanceForTile = tileChance[pair.first];
			const float actualChance = chanceForTile + totalChance;
			totalChance += chanceForTile;
			if(rand < actualChance)
			{
				result = pair.first;
				break;
			}
		}
	}
	else
	{
		const int rand = Util::RandomInt(0, (int)possibleTiles[index].size() - 1);
		result = possibleTiles[index][rand];
	}

	grid[index] = result;
	std::cout << pos.first << ", " << pos.second << "- Turned into: " << grid[index] << std::endl;
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
			std::vector<Tile> left = map.at(grid[Util::Left(i)]);
			result = Util::Intersect(result, left);
		}
		if (r)
		{
			std::vector<Tile> right = map.at(grid[Util::Right(i)]);
			result = Util::Intersect(result, right);
		}
		if (t)
		{
			std::vector<Tile> top = map.at(grid[Util::Top(i, width)]);
			result = Util::Intersect(result, top);
		}

		if (b)
		{
			std::vector<Tile> bottom = map.at(grid[Util::Bottom(i, width)]);
			result = Util::Intersect(result, bottom);
		}

		if (AdjacentEmpty(i))
		{
			possibilities[i] = result;
			entropy[i] = INT32_MAX;
			continue;
		}

		possibilities[i] = result;

		entropy[i] = (int)possibilities[i].size();
	}
}

bool Game::AdjacentEmpty(int i) const
{
	const std::vector adjacent = { Util::Left(i), Util::Right(i), Util::Top(i, width), Util::Bottom(i, width) };
	for (const int n : adjacent)
	{
		if(Util::IsOnGrid(n, grid))
		{
			if (grid[n] != TileType::EMPTY)
				return false;
		}
	}
	return true;
}
