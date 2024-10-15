#pragma once

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <map>
#include "Util.h"
#include <numeric>
#include <iostream>
#include <string>
#include "Tile.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <fstream>
#include <filesystem>
#include<set>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int width, int height);
	int collapse();
	std::vector<std::vector<Tile*>>& grid_ref();
	const std::map<std::string, Tile>& all_tiles();
	void initialise();
	void reset();
private:
	void initialise_tiles();
	void initialise_grid();
	
	int width= 0;
	int height = 0;
	std::map<std::string, Tile> tiles;
	std::vector<std::vector<Tile*>> grid;
	std::vector<Dir> directions{UP, DOWN, RIGHT, LEFT};
};

#endif