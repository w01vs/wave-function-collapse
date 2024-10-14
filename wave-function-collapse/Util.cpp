#include "Util.h"



std::vector<std::string> Util::intersect(const std::vector<std::string>& first, const std::vector<std::string>& second)
{
	std::vector<std::string> result;
	for (std::string t : first)
	{
		for (std::string t2 : second) {
			if (t == t2)
			{
				result.push_back(t);
			}
		}
	}
	return result;
}

std::vector<int> Util::min_pos(std::vector<int> vector)
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

int Util::randi(int min, int max)
{
	if (min == max)
		return min;
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}


// !! EXCLUSIVE UPPER BOUND !!
float Util::randf(float min, float max)
{
	if (max == min)
		return min;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution distr(min, max);
	return distr(eng);
}

int Util::right(int index, int width)
{
	if (index % width != width - 1)
		return index + 1;
	return -1;
}

int Util::left(int index, int width)
{
	if (index % width != width)
		return index - 1;
	return -1;
}

int Util::down(int index, int width)
{
	return index + width;
}

int Util::up(int index, int width)
{
	return index - width;
}

std::pair<int, int> Util::from_grid(int gridPos, int width, int height)
{
	int x = gridPos % height;
	int y = (gridPos - x) / width;
	return { x, y };
}

int Util::to_grid(int x, int y, int width)
{
	return y * width + x;
}