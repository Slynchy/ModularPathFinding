#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../PathAlgo.h"

#include <glm/glm.hpp>

struct NODE;

namespace PathAlgorithms
{

	class AStar : public PathAlgorithm
	{
		protected:
			float heuristic(NODE* start, NODE* goal);
			float heuristic(glm::ivec2 start, glm::ivec2 goal);
		private:
		public:
			std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};