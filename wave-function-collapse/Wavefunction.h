#pragma once

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <map>
#include "Tile.h"
#include "Util.h"
#include <numeric>
#include <iostream>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int _width, int _height, const std::map<Tile, float>& weights);
	static std::vector<std::vector<Tile>> InitPossibilitiesGrid(int width, int height, const std::vector<Tile>& tiles);
	[[nodiscard]] std::vector<Tile> GetPossibleTilesAt(int index) const;
	[[nodiscard]] std::vector<Tile> GetAllCollapsed() const;
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

#endif