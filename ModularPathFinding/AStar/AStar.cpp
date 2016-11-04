#include "AStar.h"
#include "../Node.h"

#include <map>

float PathAlgorithms::AStar::heuristic(glm::ivec2 start, glm::ivec2 goal)
{
	return glm::distance(glm::vec2(start), glm::vec2(goal));
}

bool PathAlgorithms::AStar::PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos, size_t &position)
{
	std::vector<size_t> positions;
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec.at(i)->pos == _pos->pos)
		{
			//position = i;
			positions.push_back(i);
			//return true;
		}
	}
	if(positions.size() == 0)
		return false;
	if (positions.size() > 1)
	{
		//printf("naus");
		for (size_t i = 1; i < positions.size(); i++)
		{
			_vec.erase(_vec.begin() + positions.at(i));
		}
	}
	position = positions.front();
	return true;
};

std::vector<NODE> PathAlgorithms::AStar::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	// Init the open/closed lists
	std::vector<NODE*> open;
	std::vector<NODE*> closed;
	//This is the index of new nodes, so we can delete them later
	std::vector<NODE*> index;

	// Create + setup the first node
	NODE* start = new NODE(_start);
	start->g = 0;
	start->f = heuristic(_start, _goal);

	// Push it into the open list + index
	open.push_back(start);
	index.push_back(open.front());

	while (open.size() != 0)
	{
		// Get lowest FCost then erase it from open + push it to closed
		size_t position;
		NODE* current = GetLowestFCost(open, position);
		open.erase(open.begin() + position);
		closed.push_back(current);

		// Check if current node is an obstacle
		if (_map.size() != 0)
		{
			if (
				size_t(current->pos.y) >= _map.size() ||
				size_t(current->pos.x) >= _map.at(current->pos.y).size() ||
				current->pos.y < 0 ||
				current->pos.x < 0
				) // is out of bounds
			{
				current->isObstacle = true;
				continue;
			}
			else if (_map.at(current->pos.y).at(current->pos.x)->isObstacle == true)
			{
				current->isObstacle = true;
				continue;
			}
		}
		
		bool breakout = false;
		for each (glm::ivec2* var in obstructions)
		{
			if (*var == current->pos)
			{
				breakout = true;
				current->isObstacle = true;
			}
		}
		if (breakout) continue;

		// Is the node the goal?
		if (current->pos == _goal)
		{
			closed.clear();
			open.clear();
			//obstructions.clear();
			return CleanUp(current, index); 
		}
		else
		{
			std::vector<NODE*> neighbours = GetNeighbors(current, &_map, _allowDiagonal);
			for each (NODE* var in neighbours)
			{
				index.push_back(var);
			}

			for each (NODE* var in neighbours)
			{
				float cost = 1.0f;

				if (PositionExistsInVector(open, var, position))
				{
					if ((current->g + cost) < open.at(position)->g)
					{
						open.at(position)->parent = current;
						open.at(position)->g = current->g + cost;
						open.at(position)->f = current->g + cost + heuristic(open.at(position)->pos, _goal);
					}
				}
				else if (PositionExistsInVector(closed, var, position))
				{
					if (closed.at(position)->isObstacle == true) continue;
					if ((current->g + cost) < closed.at(position)->g)
					{
						closed.at(position)->parent = current;
						closed.at(position)->g = current->g + cost;
						closed.at(position)->f = current->g + cost + heuristic(closed.at(position)->pos, _goal);
						open.push_back(closed.at(position));
						closed.erase(closed.begin() + position);
					}
				}
				else
				{
					var->parent = current;
					var->g = current->g + cost;
					var->f = current->g + cost + heuristic(var->pos, _goal);
					open.push_back(var);
				}
			}
		}

	}


	return std::vector<NODE>();
};