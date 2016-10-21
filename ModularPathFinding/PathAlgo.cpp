#include "PathAlgo.h"
#include "Node.h"

PathAlgorithm::~PathAlgorithm()
{
	//path.clear();
}

std::vector<NODE*> PathAlgorithm::GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal)
{
	std::vector<NODE*> neighbours;
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x, start->pos.y + 1)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x, start->pos.y - 1)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y)));
	neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y)));

	if (_allowDiagonal == true)
	{
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y + 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y - 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x + 1, start->pos.y - 1)));
		neighbours.push_back(new NODE(glm::ivec2(start->pos.x - 1, start->pos.y + 1)));
	}
	for each (NODE* _node in neighbours)
	{
		//_node->g = start->g + 1;
		_node->parent = start;
	}

	return neighbours;
}

std::vector<NODE> PathAlgorithm::CleanUp(NODE* current, std::vector<NODE*>& index, std::vector<NODE*>& openList, std::vector<NODE*>& closedList, std::vector<glm::ivec2>& openList_vec, std::vector<glm::ivec2>& closedList_vec)
{
	bool endreached = false;
	std::vector<NODE> result;
	while (endreached == false)
	{
		result.push_back(*current);
		if ((current->parent == nullptr))
		{
			endreached = true;
			break;
		}
		else
		{
			current = current->parent;
		}
	}
	for each (NODE* var in index)
	{
		delete var;
	}
	openList.clear();
	closedList.clear();
	openList_vec.clear();
	closedList_vec.clear();
	index.clear();
	std::reverse(result.begin(), result.end());
	return result;
}

bool PathAlgorithm::PositionExistsInVector(std::vector<glm::ivec2>& _vec, glm::ivec2 _pos)
{
	if (std::find(_vec.begin(), _vec.end(), _pos) != _vec.end())
		return true;
	return false;
};

NODE* PathAlgorithm::PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec.at(i)->pos == _pos->pos)
			return _vec.at(i);
	}
	return nullptr;
};

//DEPRECATED
size_t PathAlgorithm::GetLowestFCost(std::stack<NODE*> list)
{
	const size_t max = list.size();

	// The current lowest value, which is the first at the moment
	float lowest = list.top()->f;

	// Counter keeps track of the current index
	size_t counter = 0;

	std::size_t index = 0;
	std::size_t i = 0;

	// if only one or less elements in vector, lowest is obviously that
	if (max <= 1) return index;

	while (++counter != max) {
		NODE* current = list.top();
		list.pop();
		if (current->f < lowest) {
			lowest = current->f;
			index = i;
		}
		++i;
	}
	return index;
};

NODE* PathAlgorithm::GetLowestFCost(std::vector<NODE*>& list, size_t& position)
{
	float lowest = FLT_MAX;
	NODE* current = nullptr;
	size_t current_pos = 0;
	position = 0;
	for each (NODE* var in list)
	{
		if (var->f < lowest)
		{
			lowest = var->f;
			current = var;
			current_pos = position;
		}
		position++;
	}
	position = current_pos;
	return current;
};

//DEPRECATED
size_t PathAlgorithm::GetLowestFCost(std::vector<NODE*> list)
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

std::vector<NODE> PathAlgorithm::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	// do nothing; abstract
	return std::vector<NODE>();
};