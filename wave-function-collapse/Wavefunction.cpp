#include "Wavefunction.h"


Wavefunction::Wavefunction()
= default;

Wavefunction::Wavefunction(int width, int height)
{
	this->width = width;
	this->height = height;
	InitialiseTiles();
}

void Wavefunction::InitialiseTiles()
{
	std::string path = std::filesystem::current_path().parent_path().string() + "\\Resources\\mapped_ids.json";
	std::ifstream fs(path);
	json data = json::parse(fs);

	// Parse the initial tiles themselves, no relations
	for(auto& [key, value] : data.items())
	{
		int rot = value["rotation"].get<int>();
		std::string image = value["image"].get<std::string>();
		
		Image img = LoadImage((std::filesystem::current_path().parent_path().string() + "\\Resources\\img\\" + image).c_str());
		ImageRotate(&img, rot);
		Tile tile = {.name = key,.rotation = value["rotation"].get<int>(), .image = LoadTextureFromImage(img)};

		int id_up = value["id"]["up"].get<int>();
		int id_down = value["id"]["down"].get<int>();
		int id_right = value["id"]["right"].get<int>();
		int id_left = value["id"]["left"].get<int>();
		std::map < Dir, int> map;
		map[UP] = id_up;
		map[DOWN] = id_down;
		map[RIGHT] = id_right;
		map[LEFT] = id_left;
		
		tile.ids = std::move(map);
		tiles.insert({key, tile});
	}

	// Parse tile relations
	for(auto& [key, value] : data.items())
	{
		std::map<Dir, std::vector<Tile*>> ts;
		std::vector<std::string> up = value["map"]["up"].get<std::vector<std::string>>();
		std::vector<std::string> down = value["map"]["down"].get<std::vector<std::string>>();
		std::vector<std::string> right = value["map"]["right"].get<std::vector<std::string>>();
		std::vector<std::string> left = value["map"]["left"].get<std::vector<std::string>>();
		for(int i = 0; i < data.size() - 1; i++)
		{
			if(i < up.size())
			{
				ts[UP].push_back(&tiles.at(up.at(i)));
			}
			if(i < down.size())
			{
				ts[DOWN].push_back(&tiles.at(down.at(i)));
			}
			if(i < right.size())
			{
				ts[RIGHT].push_back(&tiles.at(right.at(i)));
			}
			if(i < left.size())
			{
				ts[LEFT].push_back(&tiles.at(left.at(i)));
			}
		}
		tiles.at(key).map = std::move(ts);
	}

	int p = 0;
}


