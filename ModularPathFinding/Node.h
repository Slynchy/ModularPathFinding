/// \file 		node.h
/// \author 	Sam Lynch
/// \details 	Definition of NODE object for use in algorithms
/// \date 		November 2016

#pragma once

#include "../glm/glm.hpp"

/// What is the default move cost to move left/right/up/down?
#define DEFAULT_MOVE_COST 1.0f

/// Definition for a NODE, used in all the algorithms
struct NODE
{
	/// Position of node
	glm::ivec2 pos;

	/// The cost to get to this NODE
	float g; 

	/// The total score of the NODE
	float f;

	/// Distance to the goal
	float h;

	/// The cost of this NODE; set to less than the default to favour it, higher to avoid it
	float cost;

	/// Is this NODE an obstacle that cannot be gone through
	bool isObstacle;

	/// The parent NODE that this NODE is derived from
	NODE* parent;

	NODE()
	{
		pos.x = 0;
		pos.y = 0;
		g = 0;
		f = 0;
		cost = DEFAULT_MOVE_COST;
		h = INFINITY;
		parent = nullptr;
		isObstacle = false;
	};
	NODE(glm::ivec2 _pos)
	{
		pos.x = _pos.x;
		pos.y = _pos.y;
		g = 0;
		f = 0;
		cost = DEFAULT_MOVE_COST;
		h = INFINITY;
		parent = nullptr;
		isObstacle = false;
	}
	NODE(glm::ivec2 _pos, bool _obstacle)
	{
		pos.x = _pos.x;
		pos.y = _pos.y;
		g = 0;
		f = 0;
		cost = DEFAULT_MOVE_COST;
		h = INFINITY;
		isObstacle = _obstacle;
		parent = nullptr;
	}
	NODE(glm::ivec2 _pos, bool _obstacle, float _gcost, float _fcost, float _h = INFINITY, float _cost = DEFAULT_MOVE_COST)
	{
		pos.x = _pos.x;
		pos.y = _pos.y;
		g = _gcost;
		f = _fcost;
		cost = _cost;
		h = _h;
		isObstacle = _obstacle;
		parent = nullptr;
	}

	/// Equality operators
	bool operator==(const NODE& b)
	{
		if (this->pos == b.pos) return true;
		return false;
	}

	/// Comparison operators
	bool operator<(const NODE& b)
	{
		if (this->f < b.f) return true;
		else return false;
	}
	bool operator>(const NODE& b)
	{
		if (this->f > b.f) return true;
		else return false;
	}
	bool operator<=(const NODE& b)
	{
		if (this->f <= b.f) return true;
		else return false;
	}
	bool operator>=(const NODE& b)
	{
		if (this->f >= b.f) return true;
		else return false;
	}

	~NODE()
	{
	}
};