#pragma once
#include <vector>
#include <map>
#include "Tile.h"
#include "Wavefunction.h"
#include <stack>

class WFModel
{
public:
	WFModel(int width, int height, const std::map<Tile, float>& weights, std::vector<Tile>& grid, const std::map<Tile, std::map<Dir, std::string>>& tilemap);
	void Run();
private:
	int Iterate();
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
	std::map<Tile, std::map<Dir, std::string>>& tilemap;
};

