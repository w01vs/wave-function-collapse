#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <string>
#include <raylib.h>
#include "Tile.h"

class Util
{
public:
	template<typename T>
	[[nodiscard]] static std::vector<T> intersect(const std::vector<T>& first, const std::vector<T>& second)
	{
		std::vector<T> result;
		for(T t : first)
		{
			for(T t2 : second)
			{
				if(t == t2)
				{
					result.push_back(t);
				}
			}
		}
		return result;
	}
	[[nodiscard]] static std::vector<int> min_pos(std::vector<int> vector);
	[[nodiscard]] static int randi(int min, int max);
	[[nodiscard]] static float randf(float min, float max);
	template<typename T, typename Y>
	[[nodiscard]] static std::vector<T> keys(const std::map<T, Y>& map)
	{
		std::vector<T> keys;
		keys.reserve(map.size());

		for(std::pair<T, Y> key : map)
		{
			keys.emplace_back(key.first);
		}
		return keys;
	}
	template <typename T, typename Y>
	[[nodiscard]] static std::vector<Y> values(const std::map<T, Y>& map)
	{
		std::vector<Y> keys;
		keys.reserve(map.size());

		for(std::pair<T, Y> key : map)
		{
			keys.emplace_back(key.second);
		}
		return keys;
	}
	template<typename T>
	[[nodiscard]] static bool contains(const std::vector<T>& vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}
	[[nodiscard]] static int right(int index, int width);
	[[nodiscard]] static int left(int index, int width);
	[[nodiscard]] static int up(int index, int width);
	[[nodiscard]] static int down(int index, int width);
	template<typename T>
	[[nodiscard]] static bool on_grid(int index, const std::vector<T>& vector)
	{
		return (size_t)index < vector.size() && index > -1;
	}
	[[nodiscard]] static std::pair<int, int> from_grid(int gridPos, int width, int height);
	[[nodiscard]] static int to_grid(int x, int y, int width);
	[[nodiscard]] static int dir_index(const int& idx, const Dir& dir, const int& width);
	[[nodiscard]] static Dir opposite(const Dir& dir);

};

#endif