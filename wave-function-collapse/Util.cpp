#include "Util.h"



std::vector<Tile> Util::Intersect(const std::vector<Tile>& first, const std::vector<Tile>& second)
{
	std::vector<Tile> result;
	for (Tile t : first)
	{
		for (Tile t2 : second) {
			if (t == t2)
			{
				result.push_back(t);
			}
		}
	}
	return result;
}

std::vector<int> Util::LowestAboveZero(std::vector<int> vector)
{
	std::vector<std::pair<int, int>> indexedVector;
	indexedVector.reserve(vector.size());

	for (int i = 0; (size_t)i < vector.size(); ++i)
	{
		indexedVector.emplace_back( vector[i], i );
	}

	std::sort(indexedVector.begin(), indexedVector.end(), [](const auto& a, const auto& b) {
		return a.first < b.first;
		});

	int smallest = 0;
	for (const std::pair<int, int>& entry : indexedVector) {
		if (entry.first > smallest) {
			smallest = entry.first;
			break;
		}
	}

	std::vector<int> indices;
	for (const std::pair<int, int>& entry : indexedVector)
	{
		if (entry.first == smallest)
		{
			indices.push_back(entry.second);
		}
		else if (entry.first > smallest)
		{
			break;
		}
	}
	return indices;
}

int Util::RandomInt(int min, int max)
{
	if (min == max)
		return min;
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}


// !! EXCLUSIVE UPPER BOUND !!
float Util::RandomFloat(float min, float max)
{
	if (max == min)
		return min;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution distr(min, max);
	return distr(eng);
}

bool Util::Filled(const std::vector<Tile>& grid)
{
	for (Tile t : grid) {
		if (t == Tile{ TileType::EMPTY }) {
			return false;
		}
	}
	return true;
}

int Util::Right(int index, int width)
{
	if (index % width != width - 1)
		return index + 1;
	return -1;
}

int Util::Left(int index, int width)
{
	if (index % width != width)
		return index - 1;
	return -1;
}

int Util::Bottom(int index, int width)
{
	return index + width;
}

int Util::Top(int index, int width)
{
	return index - width;
}

std::pair<int, int> Util ::ToPos(int gridPos, int width, int height)
{
	int x = gridPos % height;
	int y = (gridPos - x) / width;
	return { x, y };
}