#pragma once

#ifndef	WFMODEL_H
#define WFMODEL_H

#include <vector>
#include <map>
#include "Tile.h"
#include "Wavefunction.h"
#include "Direction.h"
#include <stack>
#include "Util.h"


class WFModel
{
public:
	WFModel();
	WFModel(int width, int height, const std::map<Tile, float>& weights, const std::map<Tile, std::map<Dir, std::vector<std::string>>>& tilemap);
	std::vector<Tile> Iterate();
	[[nodiscard]] bool FullyCollapsed() const;
	[[nodiscard]] std::vector<Tile> FinishedGrid() const;
private:
	void Propagate(int index);
	[[nodiscard]] int GetLowestEntropyIndex() const;
	[[nodiscard]] std::vector<Dir> ValidNeighbours(int index) const;
	[[nodiscard]] int GetNeighbour(int index, Dir direction) const;
	[[nodiscard]] bool Check(Tile tile1, Tile tile2, Dir dir, int rotation1 = 0, int rotation2 = 0) const;
	[[nodiscard]] Dir OppositeDirection(Dir dir) const;
	int width;
	int height;
	Wavefunction wavefunction;
	std::vector<Tile> grid;
	std::map<Tile, std::map<Dir, std::vector<std::string>>> tilemap;
};

#endif