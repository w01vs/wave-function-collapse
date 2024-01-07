#include "Wavefunction.h"

#include <ranges>


Wavefunction::Wavefunction()
= default;

Wavefunction::Wavefunction(int width, int height, const std::map<Tile, float>& weights)
{
	this->width = width;
	this->height = height;
	this->weights = weights;
	tiles = InitPossibilitiesGrid(width, height, Util::GetKeys(weights));
}

std::vector<std::vector<Tile>> Wavefunction::InitPossibilitiesGrid(int width, int height, const std::vector<Tile>& tiles)
{
	std::vector<std::vector<Tile>> Tiles;
	Tiles.reserve(tiles.size());
	for(int i = 0; i < width * height; ++i)
	{
		Tiles.emplace_back(tiles);
	}
	return Tiles;
}

std::vector<Tile> Wavefunction::GetPossibleTilesAt(int index) const
{
	return tiles[index];
}

std::vector<std::string> Wavefunction::GetPossibleTilesAtS(int index) const 
{
	return tilesS[index];
}



std::vector<Tile> Wavefunction::GetAllCollapsed() const
{
	std::vector<Tile> result;
	result.reserve(tiles.size());
	for(const std::vector<Tile> t : tiles)
	{
		result.emplace_back(t[0]);
	}
	return result;
}

std::vector<std::string> Wavefunction::GetAllCollapsedS() const 
{
	std::vector<std::string> result;
	result.reserve(tilesS.size());
	for (const std::vector<std::string> s : tilesS)
	{
		result.emplace_back(s[0]);
	}
	return result;
}

float Wavefunction::EntropyAt(int index) const
{
	float weightSum = 0;
	float weightSumLog = 0;
	for(const Tile t : tiles[index])
	{
		const float weight = weights.at(t);
		weightSum += weight;
		weightSumLog += weight * std::log(weight);
	}
	return std::log(weightSum) - weightSumLog / weightSum;
}


Tile Wavefunction::Collapse(int index)
{
	std::vector<std::pair<Tile, float>> filtered;
	filtered.reserve(weights.size());
	const std::vector<Tile> options = tiles[index];
	for(std::pair<Tile, float> t : weights)
	{
		if(Util::Contains(options, t.first))
			filtered.emplace_back(t);
	}

	const float totalWeight = std::accumulate(filtered.begin(), filtered.end(), 0.0f, [](float partial, const std::pair<Tile, float>& p)
	{
		return partial + p.second;
	});

	float rnd = Util::RandomFloat(0.0f, 1.0f) * totalWeight;
	Tile chosen;
	for(const std::pair<Tile,float> pair : filtered)
	{
		rnd -= pair.second;
		if (rnd < 0)
		{
			chosen = pair.first;
			break;
		}
	}

	const std::pair pos = Util::ToPos(index, width, height);
	const int x = pos.first;
	const int y = pos.second;
	std::cout << x << ", " << y << " - has turned into: " << chosen << std::endl;
	tiles[index] = { chosen };
	return chosen;
}


std::string Wavefunction::CollapseS(int index)
{
	std::vector<std::pair<std::string, float>> filtered;
	filtered.reserve(weightsS.size());
	const std::vector<std::string> options = tilesS[index];
	for (std::pair<std::string, float> t : weightsS)
	{
		if (Util::Contains(options, t.first))
			filtered.emplace_back(t);
	}

	const float totalWeight = std::accumulate(filtered.begin(), filtered.end(), 0.0f, [](float partial, const std::pair<std::string, float>& p)
		{
			return partial + p.second;
		});

	float rnd = Util::RandomFloat(0.0f, 1.0f) * totalWeight;
	std::string chosen;
	for (const std::pair<std::string, float> pair : filtered)
	{
		rnd -= pair.second;
		if (rnd < 0)
		{
			chosen = pair.first;
			break;
		}
	}

	const std::pair pos = Util::ToPos(index, width, height);
	const int x = pos.first;
	const int y = pos.second;
	std::cout << x << ", " << y << " - has turned into: " << chosen << std::endl;
	tilesS[index] = { chosen };
	return chosen;
}
void Wavefunction::RemoveTileAt(int index, Tile tile)
{
	const auto newEnd = std::remove(tiles[index].begin(), tiles[index].end(), tile);
	tiles[index].erase(newEnd, tiles[index].end());
}

void Wavefunction::RemoveTileAtS(int index, std::string tile) 
{
	const auto newEnd = std::remove(tilesS[index].begin(), tilesS[index].end(), tile);
	tilesS[index].erase(newEnd, tilesS[index].end());
}

bool Wavefunction::Collapsed() const
{
	for(size_t i = 0; i < tiles.size(); i++)
	{
		if(tiles[i].size() > 1)
		{
			return false;
		}
	}
	return true;
}
