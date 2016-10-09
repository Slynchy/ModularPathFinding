#pragma once

#include <vector>
#include "./Node.h"


class PathAlgorithm
{
protected:
	virtual NODE* PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos)
	{
		for (size_t i = 0; i < _vec.size(); i++)
		{
			if (_vec.at(i)->pos == _pos->pos)
				return _vec.at(i);
		}
		return nullptr;
	};

	virtual size_t GetLowestFCost(std::vector<NODE*>& list)
	{
		const size_t max = list.size();

		// The current lowest value, which is the first at the moment
		float lowest = list.front()->f;

		// Counter keeps track of the current index
		size_t counter = 0;

		std::size_t index = 0;
		std::size_t i = 0;

		// if only one or less elements in vector, lowest is obviously that
		if (max <= 1) return index;

		NODE* current = list.front();
		while (++counter != max) {
			++i;
			if (current->f < lowest) {
				lowest = current->f;
				index = i;
			}
		}
		return index;
	};

private:
public:

	enum ALGORITHMS
	{
		ASTAR,
		BREADTH_FIRST
	};

	std::vector<NODE> path;

	virtual std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false)
	{
		// do nothing; abstract
		return std::vector<NODE>();
	};

	~PathAlgorithm()
	{
		//path.clear();
	}
};