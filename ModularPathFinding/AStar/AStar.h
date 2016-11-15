/// \file 		AStar.h
/// \author 	Sam Lynch
/// \details 	Header file for the AStar algorithm
/// \date 		November 2016

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

	class AStar : public PathAlgorithm
	{
		protected:
			float heuristic(NODE* start, NODE* goal);
			float heuristic(glm::ivec2 start, glm::ivec2 goal);
			bool PathAlgorithms::AStar::PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos, size_t &position);
		private:
		public:
			std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};