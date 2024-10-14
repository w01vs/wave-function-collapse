#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <raylib.h>
#include <assert.h>
#include <iostream>
#include "WFModel.h"

class Game {
public:
	Game(int width, int height, int fps, const std::string& title, int cell);
	~Game() noexcept;
	Game& operator=(const Game& other) = delete;
	Game(const Game& other) = delete;
	static bool should_close();
	void tick();
private:
	
	void draw() const;
	void update();

	
	bool finished;
	int cellsize;
	int width;
	int height;
	std::vector<std::string> grid;
	std::map<std::string, float> weights;
	WFModel model;
};

#endif