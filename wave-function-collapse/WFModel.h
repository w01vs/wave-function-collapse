#pragma once

#ifndef	WFMODEL_H
#define WFMODEL_H

#include <vector>
#include <map>
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
	WFModel(int width, int height, const std::map<std::string, float>& weights, const SpriteManager& tilemap);
	[[nodiscard]] std::vector<std::string> Iterate();
	[[nodiscard]] bool FullyCollapsed() const;
	[[nodiscard]] std::vector<std::string> FinishedGridS() const;
	Wavefunction wavefunction;
private:
	void Propagate(int index);
	[[nodiscard]] int GetLowestEntropyIndex() const;
	[[nodiscard]] std::vector<Dir> ValidNeighbours(int index) const;
	[[nodiscard]] int GetNeighbour(int index, Dir direction) const;
	[[nodiscard]] bool Check(std::string tile1, std::string tile2, Dir dir) const;
	int width;
	int height;
	std::vector<std::string> grid;
	SpriteManager sprites;
};

#endif