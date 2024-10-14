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
private:
	void InitialiseTiles();
	int width= 0;
	int height = 0;
	std::map<std::string, Tile> tiles;
	std::vector<Tile*> grid;
};

#endif