#ifndef PATHALGO_H
#define PATHALGO_H

#include <vector>
#include <stack>
#include <map>

#include "../glm/glm.hpp"

struct NODE;

class PathAlgorithm
{
protected:
	typedef std::multimap<NODE*, float> OpenList;

	virtual NODE* PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos);
	virtual bool PositionExistsInVector(std::vector<glm::ivec2>& _vec, glm::ivec2 _pos);
	virtual NODE* PositionExistsInMap(OpenList& open, NODE* _node);
	virtual std::vector<NODE*> GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal);
	virtual std::vector<NODE> CleanUp(
		NODE* current,
		std::vector<NODE*>& index,
		std::vector<NODE*>& openList = std::vector<NODE*>(),
		std::vector<NODE*>& closedList = std::vector<NODE*>(),
		std::vector<glm::ivec2>& openList_vec = std::vector<glm::ivec2>(),
		std::vector<glm::ivec2>& closedList_vec = std::vector<glm::ivec2>());
	virtual NODE* GetLowestFCost(std::vector<NODE*>& list, size_t& position);
	virtual NODE* GetLowestGCost(std::vector<NODE*>& list, size_t& position);
	std::vector<glm::ivec2*> obstructions;

	//DEPRECATED
	virtual size_t GetLowestFCost(std::vector<NODE*> list);
	virtual size_t GetLowestFCost(std::stack<NODE*> list);

private:
public:

	virtual void SetAIPositions(std::vector<glm::ivec2*> _positions);
	std::vector<NODE> path;

	virtual std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);

	virtual ~PathAlgorithm();
};

#endif