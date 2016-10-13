#include "DepthFirst.h"
#include "../Node.h"

std::vector<NODE> PathAlgorithms::DepthFirst::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	std::queue<NODE*> Q;
	std::vector<NODE*> closed_list;
	std::vector<NODE*> index;
	Q.push(new NODE(_start, false));

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
			}
		};
	}

	while (Q.size() != 0)
	{
		NODE* current = Q.front();
		Q.pop();

		if (current->pos == _goal)
		{
			return CleanUp(current, index);
		}

		if (PositionExistsInVector(closed_list, current) == nullptr)
		{
			closed_list.push_back(current);
			std::vector<NODE*> neighbours = GetNeighbors(current, &_map, _allowDiagonal);
			for each (NODE* node in neighbours)
			{
				index.push_back(node);
				if (PositionExistsInVector(closed_list, node) == nullptr)
				{
					if ((size_t(node->pos.y) < _map.size() && size_t(node->pos.x) < _map.at(node->pos.y).size()))
					{
						if (_map.at(node->pos.y).at(node->pos.x)->isObstacle == true)
						{
							// It's an obstacle; close it off
							closed_list.push_back(node);
							continue;
						}
						else
						{
							Q.push(node);
						}
					}
					else
					{
						closed_list.push_back(node);
					};
				};
			}
		}
	}

	return std::vector<NODE>();
};