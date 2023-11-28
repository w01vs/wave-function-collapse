#pragma once

#include <vector>
#include <map>
#include "Tile.h"
#include "Util.h"
#include <numeric>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int _width, int _height, const std::map<Tile, float>& weights);
	static std::vector<std::vector<Tile>> InitPossibilitiesGrid(int width, int height, const std::vector<Tile>& tiles);
	[[nodiscard]] std::vector<Tile> GetPossibleTilesAt(int index) const;
	[[nodiscard]] bool Collapsed() const;
	[[nodiscard]] float EntropyAt(int index) const;
	Tile Collapse(int index);
	void RemoveTileAt(int index, Tile tile);
private:
	int width;
	int height;
	std::map<Tile, float> weights;
	std::vector<std::vector<Tile>> tiles;
};

