#include "SpriteManager.h"

SpriteManager::SpriteManager()
= default;

void SpriteManager::LoadSprites()
{
	std::cout << "Loading images" << std::endl;
	std::filesystem::path current = std::filesystem::current_path().parent_path();
	const std::filesystem::path path = current.append("Resources");
	for(const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string str = entry.path().string();
		std::string strP = str;
		const char* const p = strP.c_str();
		std::reverse(str.begin(), str.end());
		const size_t pos = str.find('\\');
		const std::string::iterator it= str.begin() + (int)pos;
		str.erase(it, str.end());
		str.erase(str.begin(), str.begin() + 4);
		std::reverse(str.begin(), str.end());
		
		Image image = LoadImage(p);
		Texture2D tex = LoadTextureFromImage(image);
		Color* colors = LoadImageColors(image);

		

		for(int i = 0; i < image.width; ++i)
		{
			colorMap[str][UP].emplace_back(colors[i]);
		}

		for(int i = 0; i < image.width; ++i)
		{
			colorMap[str][DOWN].emplace_back(colors[(image.height - 1) * image.width + i]);
		}

		for(int i = 0; i < image.height; ++i)
		{
			colorMap[str][LEFT].emplace_back(colors[(ptrdiff_t)i * image.width]);
		}

		for(int i = 0; i < image.height; ++i)
		{
			colorMap[str][RIGHT].emplace_back(colors[i * image.width + image.width - 1]);
		}

		UnloadImageColors(colors);
		textureLookup[str] = tex;
		ImageRotateCW(&image);
		tex = LoadTextureFromImage(image);
		textureLookup[str + "R90"] = tex;

		ImageRotateCW(&image);
		tex = LoadTextureFromImage(image);
		textureLookup[str + "R180"] = tex;

		ImageRotateCW(&image);
		tex = LoadTextureFromImage(image);
		textureLookup[str + "R270"] = tex;

		UnloadImage(image);
	}

	std::cout << "Finished loading images" << std::endl;
}
