#pragma once

#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include <map>
#include <string>
#include "raylib.h"
#include <iostream>
#include <filesystem>
#include "Direction.h"

class SpriteManager
{
public:
	SpriteManager();
	//Texture2D lookupTexture(std::string textureName);
	void LoadSprites();
private:
	std::map<std::string, Texture2D> textureLookup;
	std::map<std::string, std::map<Dir, std::vector<Color>>> colorMap;
};

#endif