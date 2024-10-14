#pragma once

#include <string>
#include <map>
#include <vector>

enum Dir {UP, DOWN, RIGHT, LEFT};

struct Tile
{
	std::string img;
	int rotation;
	std::map<Dir, Tile> ids;
	std::map<Dir, std::vector<Tile>> map;

};