#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "../Node.h"
#include "../PathAlgo.h"

namespace PathAlgorithms
{

	class BreadthFirst : public PathAlgorithm
	{
	protected:
	private:
	public:
		std::vector<NODE*> GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal);
		std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};