#include "BreadthFirst.h"
#include "../Node.h"

std::vector<NODE> PathAlgorithms::BreadthFirst::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	if (_map.size() == 0)
	{
		printf("BreadthFirst requires a node map!\n");
		printf("Generating one...\n");

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
			}
		};
		//return std::vector<NODE>();
	}

	std::queue<NODE*> Q;
	std::vector<glm::ivec2> used_nodes;
	std::vector<NODE*> index; 
	Q.push(new NODE(_start, false));
	index.push_back(Q.front());
	used_nodes.push_back(Q.front()->pos);

	while (Q.size() != 0)
	{
		NODE* t = Q.front();
		Q.pop();
		if (t->pos == _goal)
		{
			return CleanUp(t, index);
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
						used_nodes.push_back(node->pos);
						continue;
					}
				}
				else
				{
					used_nodes.push_back(node->pos);
					continue;
				}
			}
			if (PositionExistsInVector(used_nodes, node->pos) == false) // is not in the vector
			{
				used_nodes.push_back(node->pos);
				Q.push(node);
			}
		}
	}

	printf("BreadthFirst failed to find a path to (%i,%i)!\n", _goal.x, _goal.y);
	return std::vector<NODE>();
}