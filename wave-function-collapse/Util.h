#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "Tile.h"
#include <random>
#include <algorithm>
#include <map>
#include <raylib.h>
#include "Direction.h"

class Util
{
public:
	[[nodiscard]] static std::vector<Tile> Intersect(const std::vector<Tile>& first, const std::vector<Tile>& second);
	[[nodiscard]] static std::vector<int> LowestAboveZero(std::vector<int> vector);
	[[nodiscard]] static int RandomInt(int min, int max);
	[[nodiscard]] static float RandomFloat(float min, float max);
	[[nodiscard]] static bool Filled(const std::vector<Tile>& grid);
	template<typename T, typename Y>
	[[nodiscard]] static std::vector<T> GetKeys(const std::map<T, Y>& map)
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
	[[nodiscard]] static std::vector<Y> GetValues(const std::map<T, Y>& map)
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
	[[nodiscard]] static bool Contains(const std::vector<T>& vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}
	[[nodiscard]] static int Right(int index, int width);
	[[nodiscard]] static int Left(int index, int width);
	[[nodiscard]] static int Top(int index, int width);
	[[nodiscard]] static int Bottom(int index, int width);
	template<typename T>
	[[nodiscard]] static bool IsOnGrid(int index, const std::vector<T>& vector)
	{
		return (size_t)index < vector.size() && index > -1;
	}
	[[nodiscard]] static std::pair<int, int> ToPos(int gridPos, int width, int height);
	[[nodiscard]] static int ToGridPos(int x, int y, int width);
	[[nodiscard]] static std::vector<Color> getColor(std::string name, Dir dir, const std::map<std::string, std::map<Dir, std::vector<Color>>> colorMap);
	[[nodiscard]] static Dir OppositeDirection(const Dir dir);
};

#endif