#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "../PathAlgo.h"

#include <glm/glm.hpp>

struct NODE;

namespace PathAlgorithms
{

	class DepthFirst : public PathAlgorithm
	{
	protected:
	private:
	public:
		std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};