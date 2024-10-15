#include "WFModel.h"


WFModel::WFModel()
= default;

WFModel::WFModel(int width, int height) : wavefunction(width, height)
{
	this->width = width;
	this->height = height;
}

void WFModel::iterate()
{
	int idx = wavefunction.collapse();
	switch(idx)
	{
	case -1:
		{
		finished = true;
		return;
		}
	case -2:
		{
		impossible = true;
		return;
		}
		
	}
	propagate(idx);
}

void WFModel::check_preset()
{
	auto& grid = wavefunction.grid_ref();
	for(int i = 0; i < grid.size(); i++)
	{
		if(grid.at(i).size() == 1)
		{
			propagate(i);
		}
	}
}

void WFModel::propagate(int index)
{
	std::stack<int> stx;
	stx.push(index);

	auto& grid = wavefunction.grid_ref();

	while(!stx.empty())
	{
		int idx = stx.top();
		std::vector<Tile*>& current = grid.at(stx.top());
		stx.pop();

		for(auto& dir : directions)
		{
			int dir_idx = Util::dir_index(idx, dir, width);
			if(dir_idx < 0 || dir_idx >= grid.size())
				continue;

			if(grid.at(dir_idx).size() == 1) continue;

			std::vector<Tile*> new_tiles;
			new_tiles.reserve(wavefunction.all_tiles().size());

			for(auto* tile : current)
			{
				for(auto* option : tile->map[dir])
				{
					if(!Util::contains(new_tiles, option))
					{
						new_tiles.emplace_back(option);
					}
				}
			}


			auto result = Util::intersect(new_tiles, grid.at(dir_idx));
			if(result.size() == 0)
			{
				impossible = true;
				return;
			}
			if(result.size() == grid.at(dir_idx).size())
				continue;
			grid[dir_idx] = std::move(result);
			stx.push(dir_idx);
		}
	}
}


