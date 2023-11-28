#include "Wavefunction.h"

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
	for(int i = 0; i < width * height; ++i)
	{
		Tiles[i] = tiles;
	}
	return Tiles;
}

std::vector<Tile> Wavefunction::GetPossibleTilesAt(int index) const
{
	return tiles[index];
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
	auto options = tiles[x];
	for(std::pair<Tile, float> t : weights)
	{
		filtered.emplace_back(t);
	}

	float totalWeight = std::accumulate(filtered.begin(), filtered.end(), 0.0f, [](float partial, const std::pair<Tile, float>& p)
		{
			return partial + p.second;
		});

	float rnd = Util::RandomFloat(0.0f, 1.0f) * totalWeight;
	Tile chosen;
	for(std::pair<Tile,float> pair : filtered)
	{
		rnd -= pair.second;
		if (rnd < 0)
		{
			chosen = pair.first;
			break;
		}
	}

	tiles[index] = { chosen };
	return chosen;
}

void Wavefunction::RemoveTileAt(int index, Tile tile)
{
	const auto newEnd = std::remove(tiles[index].begin(), tiles[index].end(), tile);
	tiles[index].erase(newEnd, tiles[index].end());
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
