#pragma once

#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include <map>
#include <string>
#include "raylib.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "Direction.h"
#include "Util.h"

class SpriteManager
{
public:
	SpriteManager();
	Texture2D LookupTexture(std::string textureName) const;
	void LoadSprites();
	bool CompareColors(std::string first, std::string second, Dir dir) const;
	std::vector<std::string> images;
private:
	std::map<std::string, Texture2D> textureLookup;
	std::map<std::string, std::map<Dir, std::vector<int>>> colorMap;
};

#endif