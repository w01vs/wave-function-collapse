#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <raylib.h>
#include <assert.h>
#include <iostream>
#include <bitset>
#include <list>
#include "Util.h"
#include <raylib.h>
#include <assert.h>
#include <iostream>
#include <bitset>
#include <list>
#include "Tile.h"

class Game {
public:
	Game(int width, int height, int fps, const std::string& title);
	~Game() noexcept;
	Game& operator=(const Game& other) = delete;
	Game(const Game& other) = delete;
	static bool GameShouldClose();
	void Tick();

private:
	
	void Draw() const;
	void Update();
	void Init(int x, int y, int cell);
	void Collapse();
	void GenerateEntropy(std::vector<int>& entropy, std::vector<std::vector<Tile>>& possibilities) const;

	[[nodiscard]] bool AdjacentEmpty(int i) const;
	[[nodiscard]] int ToGridPos(int x, int y) const;
	[[nodiscard]] int Right(int index)  const;
	[[nodiscard]] int Left(int index) const;
	[[nodiscard]] int Top(int index) const;
	[[nodiscard]] int Bottom(int index) const;
	[[nodiscard]] int IsOnGrid(int index) const;
	[[nodiscard]] std::pair<int, int> ToPos(int gridPos) const;
public:

private:
	bool filled;
	int cellsize;
	int width;
	int height;
	std::vector<Tile> grid;
	std::map<Tile, std::vector<Tile>> map;
};

#endif