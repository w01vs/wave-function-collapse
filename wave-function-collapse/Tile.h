#pragma once
#ifndef TILE_H
#define TILE_H

#include "TileType.h"
#include <iostream>

class Tile {
public:
	Tile();
	Tile(TileType input);
	TileType type;
	bool operator==(const Tile& other) const;
	bool operator<(const Tile& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
	friend Tile operator&(const Tile& lhs, const Tile& rhs);
};



#endif
