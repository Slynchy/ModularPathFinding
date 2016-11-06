#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include "../PathAlgo.h"

#include "../../glm/glm.hpp"

#include "../node.h"


namespace PathAlgorithms
{

	class AStarEpsilon : public PathAlgorithm
	{
		protected:
			float heuristic(glm::ivec2 start, glm::ivec2 goal);
			NODE* PathAlgorithms::AStarEpsilon::GetBestNode(std::vector<NODE*>& list, size_t& position);
			bool PathAlgorithms::AStarEpsilon::PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos, size_t &position);
		private:
		public:
			float threshold = 1.0f;
			std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};