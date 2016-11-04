# ModularPathFinding
A C++ library for plug-play path finding with grid-based maps

# How to use
Simply bundle GLM with your application, include "Node.h" + the header for the algorithm you wish to use, and instantiate it like so:

~~~~
	PathAlgorithms::BreadthFirst* pathfinder = new PathAlgorithms::BreadthFirst();
	std::vector<std::vector<NODE*>> tempnodearray; // This would be your nodemap, but here we're going to make one
	for (size_t y = 0; y < _MAP->map.size(); y++)
	{
		std::vector<NODE*> temporary;
		for (size_t x = 0; x < _MAP->map.at(y).size(); x++)
		{
			temporary.push_back(new NODE(glm::ivec2(x, y), false));
		}
		tempnodearray.push_back(temporary);
	}
	std::vector<NODE> path = pathfinder->GeneratePath(start_position, end_position, tempnodearray);
~~~~

Your state manager will have to be configured to be able to switch the active path find module. You will also have to discretise your map into a nodemap (two-dimensional vector of NODE*).