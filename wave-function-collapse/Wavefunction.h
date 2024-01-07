#pragma once

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <map>
#include "Tile.h"
#include "Util.h"
#include <numeric>
#include <iostream>
#include <string>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int _width, int _height, const std::map<Tile, float>& weights);
	static std::vector<std::vector<Tile>> InitPossibilitiesGrid(int width, int height, const std::vector<Tile>& tiles);
	[[nodiscard]] std::vector<Tile> GetPossibleTilesAt(int index) const;
	[[nodiscard]] std::vector<std::string> GetPossibleTilesAtS(int index) const;
	[[nodiscard]] std::vector<Tile> GetAllCollapsed() const;
	[[nodiscard]] std::vector<std::string> GetAllCollapsedS() const;
	[[nodiscard]] bool Collapsed() const;
	[[nodiscard]] float EntropyAt(int index) const;
	[[nodiscard]] Tile Collapse(int index);
	[[nodiscard]] std::string CollapseS(int index);
	void RemoveTileAtS(int index, std::string tile);
	void RemoveTileAt(int index, Tile tile);
	// temp
	std::map<std::string, float> weightsS;
private:
	int width;
	int height;
	std::map<Tile, float> weights;
	std::vector<std::vector<Tile>> tiles;
	std::vector<std::vector<std::string>> tilesS;
};

#endif