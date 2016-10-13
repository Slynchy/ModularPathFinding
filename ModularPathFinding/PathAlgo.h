#ifndef PATHALGO_H
#define PATHALGO_H

#include <vector>

#include <glm/glm.hpp>

struct NODE;

class PathAlgorithm
{
protected:
	virtual NODE* PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos);
	virtual bool PositionExistsInVector(std::vector<glm::ivec2>& _vec, glm::ivec2 _pos);
	virtual std::vector<NODE*> GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal);
	virtual std::vector<NODE> CleanUp(
		NODE* current,
		std::vector<NODE*>& index,
		std::vector<NODE*>& openList = std::vector<NODE*>(),
		std::vector<NODE*>& closedList = std::vector<NODE*>(),
		std::vector<glm::ivec2>& openList_vec = std::vector<glm::ivec2>(),
		std::vector<glm::ivec2>& closedList_vec = std::vector<glm::ivec2>());
	virtual size_t GetLowestFCost(std::vector<NODE*>& list);

private:
public:

	std::vector<NODE> path;

	virtual std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);

	virtual ~PathAlgorithm();
};

#endif