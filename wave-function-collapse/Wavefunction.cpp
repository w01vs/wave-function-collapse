#include "Wavefunction.h"


Wavefunction::Wavefunction()
= default;

Wavefunction::Wavefunction(int width, int height)
{
	this->width = width;
	this->height = height;
}

int Wavefunction::collapse()
{
	std::vector<int> indices;
	indices.reserve(100);
	int ent = INT_MAX;
	for(int i = 0; i < grid.size();i++)
	{
		const std::vector<Tile*>& set = grid.at(i);
		if(set.size() == 1) continue;
		size_t s = set.size();
		if(s < ent)
		{
			indices.clear();
			ent = s;
			indices.emplace_back(i);
		}
		else if(s == ent)
		{
			indices.emplace_back(i);
		}
	}
	if(indices.size() == 0) return -1;
	int collapse_idx = indices.at(Util::randi(0, indices.size() - 1));
	if(collapse_idx == -1) return -1;
	const std::vector<Tile*>& cell = grid.at(collapse_idx);
	if(cell.size() == 0) return -2;
	std::vector<Tile*> collapsed(1);
	collapsed[0] = cell.at(Util::randi(0, cell.size() - 1));
	

	for(Dir& dir : directions)
	{
		int idx = Util::dir_index(collapse_idx, dir, width);
		if(idx < 0 || idx >= grid.size())
			continue;

		for(auto* t : grid.at(idx))
		{
			bool can = false;
			can |= !Util::contains(t->map[Util::opposite(dir)], collapsed.at(0));

			if(!can)
			{
				int x = 0;
			}
		}
		
	}
	grid[collapse_idx] = std::move(collapsed);


	return collapse_idx;
}

std::vector<std::vector<Tile*>>& Wavefunction::grid_ref()
{
	return grid;
}

const std::map<std::string, Tile>& Wavefunction::all_tiles()
{
	return tiles;
}

void Wavefunction::initialise()
{
	initialise_tiles();
	initialise_grid();
}

void Wavefunction::reset()
{
	initialise_tiles();
}

void Wavefunction::initialise_tiles()
{
	std::string path = std::filesystem::current_path().parent_path().string() + "\\Resources\\mapped_ids.json";
	std::ifstream fs(path);
	json data = json::parse(fs);

	// Parse the initial tiles themselves, no relations
	for(auto& [key, value] : data.items())
	{
		int rot = value["rotation"].get<int>();
		std::string image = value["image"].get<std::string>();
		
		std::string path = std::filesystem::current_path().parent_path().string() + "\\Resources\\img\\" + image;
		std::cerr << path;
		
		Image img = LoadImage(path.c_str());
		ImageRotate(&img, rot);
		
		Texture2D text = LoadTextureFromImage(img);
		UnloadImage(img);
		Tile tile = {.name = key,.rotation = value["rotation"].get<int>(), .image = text};

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

void Wavefunction::initialise_grid()
{
	grid.reserve(width * height);
	for(int i = 0; i < grid.capacity(); i++)
	{
		std::vector<Tile*> tiles(tiles.size());
		for(auto& [k, v] : this->tiles)
		{
			tiles.push_back(&v);
		}

		grid.push_back(tiles);
	}
}