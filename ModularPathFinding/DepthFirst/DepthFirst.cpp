#include "DepthFirst.h"
#include "../Node.h"

std::vector<NODE> PathAlgorithms::DepthFirst::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	std::stack<NODE*> S;
	std::vector<NODE*> closed_list;
	std::vector<NODE*> index;
	S.push(new NODE(_start, false));

	while (S.size() != 0)
	{
		NODE* current = S.top();
		S.pop();

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
							S.push(node);
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