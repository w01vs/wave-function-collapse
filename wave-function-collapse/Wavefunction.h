#pragma once

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <map>
#include "Util.h"
#include <numeric>
#include <iostream>
#include <string>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int _width, int _height, const std::map<std::string, float>& weights);
	static std::vector<std::vector<std::string>> InitPossibilitiesGrid(int width, int height, const std::vector<std::string>& tiles);
	[[nodiscard]] std::vector<std::string> GetPossibleTilesAt(int index) const;
	[[nodiscard]] std::vector<std::string> GetAllCollapsed() const;
	[[nodiscard]] bool Collapsed() const;
	[[nodiscard]] float EntropyAt(int index) const;
	[[nodiscard]] std::string Collapse(int index);
	void RemoveTileAt(int index, std::string tile);
private:
	int width;
	int height;
	std::map<std::string, float> weights;
	std::vector<std::vector<std::string>> tiles;
};

#endif