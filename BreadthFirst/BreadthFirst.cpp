#include <BreadthFirst.h>

std::vector<NODE*> PathAlgorithms::BreadthFirst::GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal)
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

std::vector<NODE> PathAlgorithms::BreadthFirst::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	if (_map.size() == 0)
	{
		printf("BreadthFirst requires a node map!\n");
		printf("Generating one...\n");

		int highest = 0;
		if (_start.y > highest) highest = _start.y;
		if (_goal.y > highest) highest = _goal.y;
		_map.resize(highest + 1);

		highest = 0;
		if (_start.x > highest) highest = _start.x;
		if (_goal.x > highest) highest = _goal.x;

		for (size_t y = 0; y < _map.size(); y++)
		{
			_map.at(y).resize(highest + 1);
			for (size_t x = 0; x < _map.at(y).size(); x++)
			{
				_map.at(y).at(x) = new NODE(glm::ivec2(x, y), false);
			}
		};
		//return std::vector<NODE>();
	}

	std::queue<NODE*> Q;
	std::vector<NODE*> used_nodes;
	std::vector<NODE*> index; 
	Q.push(new NODE(_start, false));
	index.push_back(Q.front());
	used_nodes.push_back(Q.front());

	while (Q.size() != 0)
	{
		NODE* t = Q.front();
		Q.pop();
		if (t->pos == _goal)
		{
			std::vector<NODE> result;
			bool endreached = false;
			while (endreached == false)
			{
				result.push_back(*t);
				if ((t->parent == nullptr))
				{
					endreached = true;
					break;
				}
				else
				{
					t = t->parent;
				}
			}
			for each (NODE* var in index)
			{
				delete var;
			}
			return result;
		}
		
		std::vector<NODE*> neighbours = GetNeighbors(t, &_map, _allowDiagonal);
		for each (NODE* node in neighbours)
		{
			index.push_back(node);
			if (_map.size() != 0)
			{
				if ((size_t(node->pos.y) < _map.size() && size_t(node->pos.x) < _map.at(node->pos.y).size()))
				{
					if (_map.at(node->pos.y).at(node->pos.x)->isObstacle == true)
					{
						// It's an obstacle; close it off
						used_nodes.push_back(node);
						continue;
					}
				}
				else
				{
					used_nodes.push_back(node);
					continue;
				}
			}
			if (PositionExistsInVector(used_nodes, node) == nullptr) // is not in the vector
			{
				used_nodes.push_back(node);
				Q.push(node);
			}
		}
	}

	printf("BreadthFirst failed to find a path to (%i,%i)!\n", _goal.x, _goal.y);
	return std::vector<NODE>();
}
