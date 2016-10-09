#include "AStar.h"

std::vector<NODE*> PathAlgorithms::AStar::GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal)
{
	std::vector<NODE*> neighbours;
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x, start->pos.y + 1)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x, start->pos.y - 1)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y)));

	if (_allowDiagonal == true)
	{
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y + 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y - 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y - 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y + 1)));
	}
	for each (NODE* _node in neighbours)
	{
		//_node->g = start->g + 1;
		_node->parent = start;
	}

	return neighbours;
}

std::vector<NODE> PathAlgorithms::AStar::GetNeighbors(NODE start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal)
{
	std::vector<NODE> neighbours;
	neighbours.push_back(NODE(glm::ivec2(start.pos.x, start.pos.y + 1)));
	neighbours.push_back(NODE(glm::ivec2(start.pos.x, start.pos.y - 1)));
	neighbours.push_back(NODE(glm::ivec2(start.pos.x + 1, start.pos.y)));
	neighbours.push_back(NODE(glm::ivec2(start.pos.x - 1, start.pos.y)));

	if (_allowDiagonal == true)
	{
		neighbours.push_back(NODE(glm::ivec2(start.pos.x + 1, start.pos.y + 1)));
		neighbours.push_back(NODE(glm::ivec2(start.pos.x - 1, start.pos.y - 1)));
		neighbours.push_back(NODE(glm::ivec2(start.pos.x + 1, start.pos.y - 1)));
		neighbours.push_back(NODE(glm::ivec2(start.pos.x - 1, start.pos.y + 1)));
	}
	for each (NODE _node in neighbours)
	{
		//_node.g = start.g + 1;
		_node.parent = &start;
	}

	return neighbours;
}

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
	std::vector<NODE*> openList;
	std::vector<NODE*> closedList;
	std::vector<NODE*> index; // for deleting data
	openList.push_back(new NODE(_start, false));
	index.push_back(openList.front());

	if (_map.size() == 0)
		printf("No node map given to AStar; expect extreme slowdown!\n");

	while (openList.size() != 0)
	{
		size_t position = GetLowestFCost(openList);
		NODE* current = openList.at(position);
		openList.erase(openList.begin() + position);
		closedList.push_back(current);

		if (current->pos == _goal)
		{
			bool endreached = false;
			std::vector<NODE> result;
			while (endreached == false)
			{
				result.push_back(*current);
				if ((current->parent == nullptr))
				{
					endreached = true;
					break;
				}
				else
				{
					current = current->parent;
				}
			}
			for each (NODE* var in index)
			{
				delete var;
			}
			openList.clear();
			closedList.clear();
			index.clear();
			return result;
		}

		std::vector<NODE*> neighbours = GetNeighbors(current, &_map, _allowDiagonal);

		for each (NODE* neighbour in neighbours)
		{
			index.push_back(neighbour);

			if (PositionExistsInVector(closedList, neighbour) != nullptr)
			{
				continue;
			}

			if (_map.size() != 0)
			{
				if ((size_t(neighbour->pos.y) < _map.size() && size_t(neighbour->pos.x) < _map.at(neighbour->pos.y).size()) && _map.at(neighbour->pos.y).at(neighbour->pos.x)->isObstacle == true)
				{
					// It's an obstacle; close it off
					closedList.push_back(neighbour);
					continue;
				}
			}

			if (PositionExistsInVector(openList, neighbour) == nullptr)
			{
				neighbour->g = current->g + 1.0f;
				neighbour->h = glm::distance(glm::vec2(_goal), glm::vec2(neighbour->pos));
				neighbour->f = neighbour->g + neighbour->h;
				//neighbour->f = (1 - (rand() % 20)) * neighbour->g + (rand() % 20) * neighbour->h;
				openList.push_back(neighbour);
			}
			else
			{
				if (neighbour->g < current->g)
				{
					neighbour->g = current->g + 1.0f;
					neighbour->h = glm::distance(glm::vec2(_goal), glm::vec2(neighbour->pos));
					neighbour->f = neighbour->g + neighbour->h;
				}
			}
		}
	}
	printf("AStar failed to find a path to (%i,%i)!\n", _goal.x, _goal.y);
	return std::vector<NODE>();
};