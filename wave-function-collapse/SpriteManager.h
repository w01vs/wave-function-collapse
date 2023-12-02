#pragma once

#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include <map>
#include <string>
#include "raylib.h"
#include <iostream>
#include <filesystem>

class SpriteManager
{
public:
	SpriteManager();
	//Texture2D lookupTexture(std::string textureName);
	void LoadSprites();
private:
	std::map<std::string, Texture2D> textureLookup;
};

#endif