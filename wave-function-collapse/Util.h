#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "Tile.h"
#include <random>
#include <algorithm>
#include <map>

class Util
{
public:
	static std::vector<Tile> Intersect(std::vector<Tile> first, std::vector<Tile> second);
	static std::vector<int> LowestAboveZero(std::vector<int> vector);
	static int RandomInt(int min, int max);
	static bool Filled(std::vector<Tile> grid);
	template<typename T, typename Y>
	static std::vector<T> GetKeys(const std::map<T, Y> map)
	{
		std::vector<T> keys;
		keys.reserve(map.size());

		for (std::pair<T, Y> key : map)
		{
			keys.emplace_back(key.first);
		}
		return keys;
	}
	template <typename T, typename Y>
	static std::vector<Y> GetValues(const std::map<T, Y> map)
	{
		std::vector<Y> keys;
		keys.reserve(map.size());

		for (std::pair<T, Y> key : map)
		{
			keys.emplace_back(key.second);
		}
		return keys;
	}
	template<typename T>
	static bool Contains(std::vector<T> vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}

};

#endif