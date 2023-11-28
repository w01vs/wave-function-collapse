#include "WFModel.h"


WFModel::WFModel()
= default;

WFModel::WFModel(int width, int height, const std::map<Tile, float>& weights, const std::map<Tile, std::map<Dir, std::vector<std::string>>>& tilemap)
{
	this->width = width;
	this->height = height;
	wavefunction = Wavefunction(width, height, weights);
	this->tilemap = tilemap;
	for(int i = 0; i < width * height; ++i)
	{
		grid.emplace_back(TileType::EMPTY);
	}
}

std::vector<Tile> WFModel::Iterate()
{
	const int index = GetLowestEntropyIndex();
	grid[index] = wavefunction.Collapse(index);
	Propagate(index);

	return grid;
}

bool WFModel::FullyCollapsed() const
{
	return wavefunction.Collapsed();
}

std::vector<Tile> WFModel::FinishedGrid() const
{
	return wavefunction.GetAllCollapsed();
}

void WFModel::Propagate(int index)
{
	std::stack<int> stack;
	stack.push(index);
	while(!stack.empty())
	{
		const int current = stack.top();
		stack.pop();
		std::vector<Tile> possibleTiles = wavefunction.GetPossibleTilesAt(current);
		for(const Dir dir : ValidNeighbours(current))
		{
			const int otherIndex = GetNeighbour(current, dir);
			for(const Tile otherTile : wavefunction.GetPossibleTilesAt(otherIndex))
			{
				bool tilePossible = false;
				for(const Tile tile : possibleTiles)
				{
					tilePossible |= Check(tile, otherTile, dir);
				}

				if (!tilePossible)
				{
					wavefunction.RemoveTileAt(otherIndex, otherTile);
					stack.push(otherIndex);
				}
			}
		}
	}
}

int WFModel::GetLowestEntropyIndex() const
{
	const float* minEntropy = nullptr;
	int index = 0;
	for(int i = 0; (size_t)i < grid.size(); ++i)
	{
		if (wavefunction.GetPossibleTilesAt(i).size() == 1) continue;

		const float entropy = wavefunction.EntropyAt(i);
		float noisedEntropy = entropy - Util::RandomFloat(0, 1) / 1000;
		if(!minEntropy or noisedEntropy < *minEntropy)
		{
			minEntropy = &noisedEntropy;
			index = i;
		}
	}

	return index;
}

std::vector<Dir> WFModel::ValidNeighbours(int index) const
{
	std::vector<Dir> result;
	if (Util::IsOnGrid(Util::Right(index, width), grid)) result.emplace_back(RIGHT);
	if (Util::IsOnGrid(Util::Left(index, width), grid)) result.emplace_back(LEFT);
	if (Util::IsOnGrid(Util::Top(index, width), grid)) result.emplace_back(UP);
	if (Util::IsOnGrid(Util::Bottom(index, width), grid)) result.emplace_back(DOWN);
	return result;
}

int WFModel::GetNeighbour(int index, Dir direction) const
{
	switch(direction)
	{
	case UP:
		if (Util::IsOnGrid(Util::Top(index, width), grid)) return Util::Top(index, width);
		break;
	case DOWN:
		if (Util::IsOnGrid(Util::Bottom(index, width), grid)) return Util::Bottom(index, width);
		break;
	case RIGHT:
		if (Util::IsOnGrid(Util::Right(index, width), grid)) return Util::Right(index, width);
		break;
	case LEFT:
		if (Util::IsOnGrid(Util::Left(index, width), grid)) return Util::Left(index, width);
		break;
	}
	
	return -1;
}

bool WFModel::Check(Tile tile1, Tile tile2, Dir dir, int rotation1, int rotation2) const
{
	//if (tilemap.at(tile1).at(dir) == tilemap.at(tile2).at(OppositeDirection(dir))) return true;
	switch(tile1.type)
	{
	case TileType::BEACH:
		if (tile2 == TileType::WATER or tile2 == TileType::BEACH or tile2 == TileType::GRASS) return true;
		break;
	case TileType::GRASS:
		if (tile2 == TileType::GRASS or tile2 == TileType::BEACH) return true;
		break;
	case TileType::WATER:
		if (tile2 == TileType::WATER or tile2 == TileType::BEACH) return true;
		break;
	default:
		break;
	}
	return false;
}


Dir WFModel::OppositeDirection(const Dir dir) const
{
	switch(dir)
	{
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case RIGHT:
		return LEFT;
	case LEFT:
		return RIGHT;
	}

	return UP;
}
