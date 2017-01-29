#include "Dijkstra.h"
#include "../Node.h"
#include <vector>

NODE* GetShortestDist(std::vector<NODE*>& list, glm::ivec2 _goal, size_t& pos)
{
	float lowest = FLT_MAX;
	NODE* current = nullptr;
	size_t current_pos = 0;
	pos = 0;
	for each (NODE* var in list)
	{
		if (glm::distance(glm::vec2(var->pos), glm::vec2(_goal)) < lowest)
		{
			lowest = glm::distance(glm::vec2(var->pos), glm::vec2(_goal));
			current = var;
			current_pos = pos;
		}
		pos++;
	}
	pos = current_pos;
	return current;
}

std::vector<NODE> PathAlgorithms::Dijkstra::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	std::vector<NODE*> open;
	std::vector<NODE*> closed;
	std::vector<NODE*> index;
	NODE* start = new NODE();
	start->pos = _start;
	start->g = 0;
	open.push_back(start);
	index.push_back(start);

	while (open.size() != 0)
	{
		size_t pos;
		NODE* current = GetShortestDist(open, _goal, pos);
		open.erase(open.begin() + pos);
		closed.push_back(current);

		if (current->pos == _goal)
		{
			printf("goal!\n");
			closed.clear();
			open.clear();
			return CleanUp(current, index);
		}

		std::vector<NODE*> neighbours = GetNeighbors(current, &_map, _allowDiagonal);
		for each (NODE* var in neighbours)
		{
			var->g = FLT_MAX;
			index.push_back(var);
		}

		for each (NODE* var in neighbours)
		{
			if (PositionExistsInVector(closed, var) || PositionExistsInVector(open, var))
			{
				continue;
			}

			if (_map.size() != 0)
			{
				if (
					size_t(var->pos.y) >= _map.size() ||
					size_t(var->pos.x) >= _map.at(var->pos.y).size() ||
					var->pos.y < 0 ||
					var->pos.x < 0
					) // is out of bounds
				{
					var->isObstacle = true;
					closed.push_back(var);
					continue;
				}
				else if (_map.at(var->pos.y).at(var->pos.x)->isObstacle == true)
				{
					var->isObstacle = true;
					closed.push_back(var);
					continue;
				};
			}

			float alt =  // distance between current and start + distance between current and neighbour (usually 1)
				glm::distance(
					glm::vec2(current->pos), 
					glm::vec2(_start)
				) + 
				glm::distance(
					glm::vec2(current->pos), 
					glm::vec2(var->pos)
				);
			var->g = alt;
			open.push_back(var);
		};
	}


	return std::vector<NODE>();
};