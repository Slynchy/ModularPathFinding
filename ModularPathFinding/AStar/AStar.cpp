#include "AStar.h"
#include "../Node.h"

float PathAlgorithms::AStar::heuristic(NODE* start, NODE* goal)
{
	int dx = abs(start->pos.x - goal->pos.x);
	int dy = abs(start->pos.y - goal->pos.y);
	return 1.0f * (dx + dy);
}

float PathAlgorithms::AStar::heuristic(glm::ivec2 start, glm::ivec2 goal)
{
	return 1.0f * (abs(start.x - goal.x) + abs(start.y - goal.y));
}

std::vector<NODE> PathAlgorithms::AStar::GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	printf("AStar failed to find a path to (%i,%i)!\n", _goal.x, _goal.y);
	return std::vector<NODE>();
};