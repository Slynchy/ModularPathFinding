#include "AStar.h"
#include "../Node.h"

float PathAlgorithms::AStar::heuristic(NODE* start, NODE* goal)
{
	int dx = abs(start->pos.x - goal->pos.x);
	int dy = abs(start->pos.y - goal->pos.y);
	return 1.0f * (dx + dy);
}

float PathAlgorithms::AStar::heuristic(glm::ivec2 start, glm::ivec2 goal)
{
	return 1.0f * (abs(start.x - goal.x) + abs(start.y - goal.y));
}

std::vector<NODE> PathAlgorithms::AStar::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	std::vector<NODE*> openList; // List of nodes to check
	//std::vector<NODE*> closedList; // List of nodes that have already been checked
	std::vector<glm::ivec2> openList_vec; // List of node positions
	std::vector<glm::ivec2> closedList; // List of node positions
	std::vector<NODE*> index; // for deleting data

	// Push the start point to the open list + its position
	openList.push_back(new NODE(_start, false));
	openList_vec.push_back(_start);
	index.push_back(openList.front());

	if (_map.size() == 0)
	{
		int highest = 0;
		if (_start.y > highest) highest = _start.y;
		if (_goal.y > highest) highest = _goal.y;
		_map.resize(highest);

		highest = 0;
		if (_start.x > highest) highest = _start.x;
		if (_goal.x > highest) highest = _goal.x;

		for (size_t y = 0; y < _map.size(); y++)
		{
			_map.at(y).resize(highest);
			for (size_t x = 0; x < _map.at(y).size(); x++)
			{
				_map.at(y).at(x) = new NODE(glm::ivec2(x, y), false);
				index.push_back(_map.at(y).at(x));
			}
		};
	}

	while (openList.size() != 0)
	{
		size_t position = GetLowestFCost(openList);
		NODE* current = openList.at(position);
		openList.erase(openList.begin() + position);
		openList_vec.erase(openList_vec.begin() + position);
		//closedList.push_back(current);
		//closedList_vec.push_back(current->pos);
		closedList.push_back(current->pos);

		if (current->pos == _goal)
		{
			closedList.clear();
			openList_vec.clear();
			return CleanUp(current, index, openList); //, closedList, openList_vec, closedList_vec);
		}

		std::vector<NODE*> neighbours = GetNeighbors(current, &_map, _allowDiagonal);

		for each (NODE* neighbour in neighbours)
		{
			neighbour->g = current->g + 1.0f;
			neighbour->h = glm::distance(glm::vec2(_goal), glm::vec2(neighbour->pos));
			neighbour->f = neighbour->g + neighbour->h;
			index.push_back(neighbour);

			if (PositionExistsInVector(closedList, neighbour->pos) == true)
			{
				continue;
			}

			if (_map.size() != 0)
			{
				if (
					size_t(neighbour->pos.y) >= _map.size() || 
					size_t(neighbour->pos.x) >= _map.at(neighbour->pos.y).size() ||
					neighbour->pos.y < 0 ||
					neighbour->pos.x < 0
					) // is above or less the size
				{
					//closedList.push_back(neighbour);
					closedList.push_back(neighbour->pos);
					continue;
				}
				else if(_map.at(neighbour->pos.y).at(neighbour->pos.x)->isObstacle == true)
				{
					//closedList.push_back(neighbour);
					closedList.push_back(neighbour->pos);
					continue;
				}
				//if ((size_t(neighbour->pos.y) >= _map.size() && 
				//	size_t(neighbour->pos.x) >= _map.at(neighbour->pos.y).size()) ||
				//	_map.at(neighbour->pos.y).at(neighbour->pos.x)->isObstacle == true)
				//{
				//	// It's an obstacle; close it off
				//	closedList.push_back(neighbour);
				//	continue;
				//}
			}

			if (PositionExistsInVector(openList_vec, neighbour->pos) == false)
			{
				neighbour->g = current->g + 1.0f;
				neighbour->h = glm::distance(glm::vec2(_goal), glm::vec2(neighbour->pos));
				neighbour->f = neighbour->g + neighbour->h;
				//neighbour->f = (1 - (rand() % 20)) * neighbour->g + (rand() % 20) * neighbour->h;
				openList.push_back(neighbour);
				openList_vec.push_back(neighbour->pos);
			}
			else
			{
				//nothing
			}
		}
	}
	printf("AStar failed to find a path to (%i,%i)!\n", _goal.x, _goal.y);
	return std::vector<NODE>();
};