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
#include "Tile.h"
#include "Direction.h"
#include "WFModel.h"
#include "SpriteManager.h"

class Game {
public:
	Game(int width, int height, int fps, const std::string& title, int cell);
	~Game() noexcept;
	Game& operator=(const Game& other) = delete;
	Game(const Game& other) = delete;
	static bool GameShouldClose();
	void Tick();
private:
	
	void Draw() const;
	void Update();

	
	bool finished;
	int cellsize;
	int width;
	int height;
	std::vector<Tile> grid;
	std::vector<std::string> ngrid;
	std::map<Tile, std::map<Dir, std::vector<std::string>>> map;
	std::map<Tile, float> weights;
	WFModel model;
	SpriteManager sprites;
};

#endif