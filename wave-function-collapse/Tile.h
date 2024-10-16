#pragma once

#ifndef TILE_H

#define TILE_H


#include <string>
#include <map>
#include <vector>
#include <raylib.h>


enum Dir {UP, DOWN, RIGHT, LEFT};

struct Tile
{
	std::string name;
	int rotation;
	std::map<Dir, int> ids;
	std::map<Dir, std::vector<Tile*>> map;
	Texture2D image;
}; 
#endif // !TILE_H