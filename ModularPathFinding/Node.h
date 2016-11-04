#pragma once

#include "../glm/glm.hpp"

struct NODE
{
	glm::ivec2 pos;
	float g, f, h;
	bool isObstacle;
	NODE* parent;
	NODE()
	{
		pos.x = 0;
		pos.y = 0;
		g = 0;
		f = 0;
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
		h = INFINITY;
		isObstacle = _obstacle;
		parent = nullptr;
	}
	NODE(glm::ivec2 _pos, bool _obstacle, float _gcost, float _fcost, float _h = INFINITY)
	{
		pos.x = _pos.x;
		pos.y = _pos.y;
		g = _gcost;
		f = _fcost;
		h = _h;
		isObstacle = _obstacle;
		parent = nullptr;
	}
	bool operator==(const NODE& b)
	{
		if (this->pos == b.pos) return true;
		return false;
	}
	~NODE()
	{
	}
};