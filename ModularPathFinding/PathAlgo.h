/// \file 		pathalgo.h
/// \author 	Sam Lynch
/// \details 	Definition of base class for all path finding algorithms
/// \date 		November 2016

#ifndef PATHALGO_H
#define PATHALGO_H

#include <vector>
#include <stack>
#include <map>

#include "../glm/glm.hpp"

struct NODE;

/// The abstract/parent class for all pathfinder algorithms
class PathAlgorithm
{
protected:
	/// \deprecated Was used by AStar but didn't work
	typedef std::multimap<NODE*, float> OpenList;

	/// Checks if the NODE exists in the vector, and returns it
	/// \deprecated Most algorithms have their own version of this, queued for update/removal
	virtual NODE* PositionExistsInVector(std::vector<NODE*>& _vec, NODE* _pos);

	/// Checks if the NODE exists in the vector
	/// \deprecated I'll be honest, I have no clue what this one does.
	virtual bool PositionExistsInVector(std::vector<glm::ivec2>& _vec, glm::ivec2 _pos);

	/// \deprecated Was used by AStar but didn't work
	virtual NODE* PositionExistsInMap(OpenList& open, NODE* _node);

	/// Creates a vector of nodes with the neighbouring positions of the provided NODE
	/// \param start The NODE to get neighbours for
	/// \param _nmap The node map (not required, can just pass a basic constructor)
	/// \param _allowDiagonal Generate the diagonal neighbours if true
	virtual std::vector<NODE*> GetNeighbors(NODE* start, std::vector<std::vector<NODE*>>* _nmap, bool _allowDiagonal, std::vector<NODE*>& _index = std::vector<NODE*>());

	/// Cleans up the algorith and returns the path
	/// \param current The final node with which to generate the path
	/// \param index The index of instantiated memory so that it can be deleted and prevent memory leaks
	/// \param openList [OPTIONAL] Clears the open list
	/// \param closedList [OPTIONAL] Clears the closed list
	/// \param openList_vec [OPTIONAL] Clears the open list of vectors
	/// \param closedList_vec [OPTIONAL] Clears the closed list of vectors
	virtual std::vector<NODE> CleanUp(
		NODE* current,
		std::vector<NODE*>& index,
		std::vector<NODE*>& openList = std::vector<NODE*>(),
		std::vector<NODE*>& closedList = std::vector<NODE*>(),
		std::vector<glm::ivec2>& openList_vec = std::vector<glm::ivec2>(),
		std::vector<glm::ivec2>& closedList_vec = std::vector<glm::ivec2>()
	);

	/// Gets the lowest F cost from the provided list
	virtual NODE* GetLowestFCost(std::vector<NODE*>& list, size_t& position);

	/// Gets the lowest G cost from the provided list
	virtual NODE* GetLowestGCost(std::vector<NODE*>& list, size_t& position);

	/// Contains a list of dynamic obstructions (e.g. other agents)
	std::vector<glm::ivec2*> obstructions;

	/// \deprecated Use the other lowestFCost function
	virtual size_t GetLowestFCost(std::vector<NODE*> list);

	/// \deprecated Use the other lowestFCost function
	virtual size_t GetLowestFCost(std::stack<NODE*> list);

private:
public:

	/// Updates the obstructions variable
	virtual void SetAIPositions(std::vector<glm::ivec2*> _positions);

	/// The resulting path; will be "size() == 0" if one wasn't found
	std::vector<NODE> path;

	/// The actual path generator!
	virtual std::vector<NODE> GeneratePath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);

	/// Destructor
	virtual ~PathAlgorithm();
};

#endif