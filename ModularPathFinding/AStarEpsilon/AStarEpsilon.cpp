#include "AStarEpsilon.h"
#include "../Node.h"

#include <queue>

float PathAlgorithms::AStarEpsilon::heuristic(glm::ivec2 start, glm::ivec2 goal)
{
	return glm::distance(glm::vec2(start), glm::vec2(goal));
}

// Exclusive to A*epsilon
// Configure to suit your needs
NODE* PathAlgorithms::AStarEpsilon::GetBestNode(std::vector<NODE*>& list, size_t& position)
{
	// Get (one of) the lowest F cost as a starting point
	NODE* best = GetLowestFCost(list, position);

	// Init the list of suitable nodes
	std::vector<NODE*> test;
	std::vector<size_t> positions;
	//std::priority_queue<NODE*> test;

	// Iterate through the list and find any within the threshold
	size_t counter = 0;
	for each (NODE* var in list)
	{
		if (var->f <= (best->f + threshold))
		{
			//test.push(var);
			test.push_back(var);
			positions.push_back(counter);
		}
		counter++;
	}

	// Here, select your criteria for picking one
	// I'm going to get the lowest G cost
	size_t temp;
	best = GetLowestGCost(test, temp);
	position = positions.at(temp);

	//return test.top();
	return best;
}

bool PathAlgorithms::AStarEpsilon::PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos, size_t &position)
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
		for (size_t i = 1; i < positions.size(); i++)
		{
			_vec.erase(_vec.begin() + positions.at(i));
		}
	}
	position = positions.front();
	return true;
};

std::vector<NODE> PathAlgorithms::AStarEpsilon::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
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
		NODE* current = PathAlgorithms::AStarEpsilon::GetBestNode(open, position);
		open.erase(open.begin() + position);
		closed.push_back(current);
		
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
				//float cost = 1.0f;
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
					}
					else 
					{
						var->cost = _map.at(var->pos.y).at(var->pos.x)->cost;
					}
				}

				if (PositionExistsInVector(open, var, position))
				{
					if ((current->g + open.at(position)->cost) < open.at(position)->g)
					{
						open.at(position)->parent = current;
						open.at(position)->g = current->g + open.at(position)->cost;
						open.at(position)->f = current->g + open.at(position)->cost + heuristic(open.at(position)->pos, _goal);
					}
				}
				else if (PositionExistsInVector(closed, var, position))
				{
					if (closed.at(position)->isObstacle == true) continue;
					if ((current->g + closed.at(position)->cost) < closed.at(position)->g)
					{
						closed.at(position)->parent = current;
						closed.at(position)->g = current->g + closed.at(position)->cost;
						closed.at(position)->f = current->g + closed.at(position)->cost + heuristic(closed.at(position)->pos, _goal);
						open.push_back(closed.at(position));
						closed.erase(closed.begin() + position);
					}
				}
				else
				{
					var->parent = current;
					var->g = current->g + var->cost;
					var->f = current->g + var->cost + heuristic(var->pos, _goal);
					open.push_back(var);
				}
			}
		}

	}


	return std::vector<NODE>();
};