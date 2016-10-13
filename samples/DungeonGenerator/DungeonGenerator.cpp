#include "DungeonGenerator.h"
#include "include\Node.h"
#include "include\SDL2\SDL.h"
#include "include\ModularPathFinding\AStar\AStar.h"
#include "include\ModularPathFinding\BreadthFirst\BreadthFirst.h"

Level::Level(glm::ivec2 _size)
{
	texture = nullptr;
	ClearMap(_size);
}

void Level::ClearMap()
{
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map.at(y).size(); x++)
		{
			map.at(y).at(x) = 1;
		}
	}
}

void Level::UpdateNodeMap()
{
	for (size_t y = 0; y < nmap.size(); y++)
	{
		for (size_t x = 0; x < nmap.at(y).size(); x++)
		{
			delete nmap.at(y).at(x);
		}
		nmap.at(y).clear();
	}
	nmap.clear();
	for (size_t y = 0; y < map.size(); y++)
	{
		std::vector<NODE*> temp;
		for (size_t x = 0; x < map.at(y).size(); x++)
		{
			if (map.at(y).at(x) == 1)
			{
				temp.push_back(new NODE(glm::ivec2(x, y), true));
			}
			else
			{
				temp.push_back(new NODE(glm::ivec2(x, y), false));
			}
		}
		nmap.push_back(temp);
	}
};

void Level::ClearMap(glm::ivec2 _size)
{
	for (size_t y = 0; y < size_t(_size.y); y++)
	{
		std::vector<int> temp;
		map.push_back(temp);
		for (size_t x = 0; x < size_t(_size.x); x++)
		{
			map.at(y).push_back(1);
		}
	}
}

void Level::Reset()
{
	rooms.clear();
	ClearMap();
	if(texture != nullptr) SDL_DestroyTexture(texture);
}

void DungeonGenerator::PlaceRoom(Level* _MAP, glm::ivec2 _pos, glm::ivec2 _size, int _type)
{
	std::vector<std::vector<int>>* MAP = &_MAP->map;
	for (size_t y = 0; y < size_t(_size.y); y++)
	{
		for (size_t x = 0; x < size_t(_size.x); x++)
		{
			MAP->at(y + _pos.y).at(x + _pos.x) = _type;
		};
	};
	ROOM tempRoom;
	tempRoom.pos = _pos;
	tempRoom.size = _size;
	_MAP->rooms.push_back(tempRoom);
}

void DungeonGenerator::PopulateWithRooms(Level* _MAP, unsigned int _roomcount)
{
	_MAP->rooms.clear();
	std::vector<std::vector<int>>* MAP = &_MAP->map;
	unsigned int MAPY = MAP->size();
	unsigned int MAPX = MAP->at(0).size();
	unsigned int roomCount = 0;
	while (roomCount < _roomcount)
	{
		glm::ivec2 breakout = glm::ivec2();

		unsigned int initialRoomWidth = rand() % 6 + 4;
		size_t testX = rand() % (MAPX - initialRoomWidth); // where the room will go X
		size_t testY = rand() % (MAPY - initialRoomWidth); // where the room will go Y
		if (testX == 0) testX++;
		if (testY == 0) testY++;

		bool conflict = false;
		for (size_t y = 0; y < initialRoomWidth; y++)
		{
			for (size_t x = 0; x < initialRoomWidth; x++)
			{
				if (MAP->at(y + testY).at(x + testX) == 1)
				{
					conflict = true;
				}
				else
				{
					//breakout = nullptr;
				};
			};
		};
		// if it exceeds vector size
		if (conflict == false && MAP->size() <= (testY + initialRoomWidth))
		{
			// do nothing since breakout is still null anyway
		}
		else
		{
			if (MAP->at(0).size() <= (testX + initialRoomWidth))
			{
				// do nothing since breakout is still null anyway
			}
			else
			{
				// shouldn't be OOB, so lets do it
				breakout = glm::ivec2(testX, testY);
			}
		}

		if (breakout != glm::ivec2())
		{
			glm::vec2 size = { (float)initialRoomWidth, (float)initialRoomWidth };
			PlaceRoom(_MAP, breakout, size, 0);

			roomCount++;
		};
	};
}

void DungeonGenerator::ConnectRooms(Level* _MAP)
{
	// init path variable + pathfinder
	std::vector<NODE> path;
	PathAlgorithms::BreadthFirst* pathfinder = new PathAlgorithms::BreadthFirst();

	// Create the temporary empty node array for the pathfinder to use
	std::vector<std::vector<NODE*>> tempnodearray;
	for (size_t y = 0; y < _MAP->map.size(); y++)
	{
		std::vector<NODE*> temporary;
		for (size_t x = 0; x < _MAP->map.at(y).size(); x++)
		{
			temporary.push_back(new NODE(glm::ivec2(x, y), false));
		}
		tempnodearray.push_back(temporary);
	}

	// for every room (barring the last one
	for (size_t i = 0; i < (_MAP->rooms.size() - 1); i++)
	{
		std::vector<NODE> path = pathfinder->GeneratePath(_MAP->rooms.at(i).pos, _MAP->rooms.at(i + 1).pos, tempnodearray, false);
		for each (NODE var in path)
		{
			_MAP->map.at(var.pos.y).at(var.pos.x) = 0;
		}
	}

	delete pathfinder;
	for (size_t y = 0; y < tempnodearray.size(); y++)
	{
		for (size_t x = 0; x < tempnodearray.at(y).size(); x++)
		{
			delete tempnodearray.at(y).at(x);
		}
	}

	return;
}

void DungeonGenerator::GenerateTexture(SDL_Renderer* _renderer, Level* _MAP)
{
	_MAP->texture = SDL_CreateTexture(_renderer, NULL, SDL_TEXTUREACCESS_TARGET, 640, 480);
	SDL_SetRenderTarget(_renderer, _MAP->texture);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
	for (size_t y = 0; y < _MAP->map.size(); y++)
	{
		for (size_t x = 0; x < _MAP->map.at(y).size(); x++)
		{
			if (_MAP->map.at(y).at(x) != 1)
			{
				SDL_Rect temp = { 8 + (8 * (int)x) ,  8 + (8 * (int)y), 8,8 };
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(_renderer, &temp);

				temp.x = 9 + (8 * x);  //x
				temp.y = 9 + (8 * y);	//y
				temp.w = 6;			//w
				temp.h = 6;			//h
				SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
				SDL_RenderFillRect(_renderer, &temp);
			}
		}
	}
	SDL_SetRenderTarget(_renderer, NULL);
	return;
}