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
#include "SpriteManager.h"
#include <string>

class WFModel
{
public:
	WFModel();
	WFModel(int width, int height, const std::map<Tile, float>& weights, const SpriteManager& tilemap);
	[[nodiscard]] std::vector<Tile> Iterate();
	[[nodiscard]] std::vector<std::string> IterateS();
	[[nodiscard]] bool FullyCollapsed() const;
	[[nodiscard]] std::vector<Tile> FinishedGrid() const;
	[[nodiscard]] std::vector<std::string> FinishedGridS() const;
	Wavefunction wavefunction;
private:
	void Propagate(int index);
	void PropagateS(int index);
	[[nodiscard]] int GetLowestEntropyIndex() const;
	[[nodiscard]] std::vector<Dir> ValidNeighbours(int index) const;
	[[nodiscard]] int GetNeighbour(int index, Dir direction) const;
	[[nodiscard]] bool Check(Tile tile1, Tile tile2, Dir dir, int rotation1 = 0, int rotation2 = 0) const;
	[[nodiscard]] bool CheckS(std::string tile1, std::string tile2, Dir dir) const;
	int width;
	int height;
	std::vector<Tile> grid;
	std::vector<std::string> ngrid;
	SpriteManager sprites;
};

#endif