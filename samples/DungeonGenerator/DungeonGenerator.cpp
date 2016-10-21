#include "DungeonGenerator.h"
#include "include\Node.h"
#include "include\SDL2\SDL.h"
#include "include\ModularPathFinding\AStar\AStar.h"
#include "include\ModularPathFinding\BreadthFirst\BreadthFirst.h"
#include "include\ModularPathFinding\BestFirst\BestFirst.h"

#include "include\GameObject.h"
#include "include\SDL2\SDL_image.h"

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
		std::vector<NODE> path = pathfinder->GeneratePath(_MAP->rooms.at(i).pos, _MAP->rooms.at(i + 1).pos + (_MAP->rooms.at(i + 1).size / 2), tempnodearray, false);
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
	SDL_Texture* floor = IMG_LoadTexture(_renderer, "./floor.png");
	SDL_Texture* wall = IMG_LoadTexture(_renderer, "./wall.png");
	SDL_Texture* randomobjects = IMG_LoadTexture(_renderer, "./objects.png");

	_MAP->texture = SDL_CreateTexture(_renderer, NULL, SDL_TEXTUREACCESS_TARGET, _MAP->map.at(0).size() * 16, _MAP->map.size() * 16);

	_MAP->texture_rect = new SDL_Rect();
	SDL_QueryTexture(_MAP->texture, NULL, NULL, &_MAP->texture_rect->w, &_MAP->texture_rect->h);
	_MAP->texture_rect->h *= 3;
	_MAP->texture_rect->w *= 3;

	SDL_SetRenderTarget(_renderer, _MAP->texture);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
	for (size_t y = 0; y < _MAP->map.size(); y++)
	{
		for (size_t x = 0; x < _MAP->map.at(y).size(); x++)
		{


			int sprite_size = 16;
			SDL_Rect temp = { 0 + (sprite_size * (int)x) ,  0 + (sprite_size * (int)y), sprite_size,sprite_size };
			if (_MAP->map.at(y).at(x) != 1)
			{

				SDL_RenderCopy(_renderer, floor, NULL, &temp);
				if (rand() % 30 == 0)
				{
					//SDL_Rect srctemp = { 16 * 0, 0, 16,16 };
					_MAP->scene_graph_ptr->push_back(new GameObject(glm::ivec2(x, y), _MAP, "Treasure"));
					_MAP->scene_graph_ptr->back()->SetActiveSprite(randomobjects);
					//SDL_RenderCopy(_renderer, randomobjects, &srctemp, &temp);
				}
				//SDL_RenderFillRect(_renderer, &temp);
			}
			else
			{
				uint8_t type = 0;

				if ((y - 1) != SIZE_MAX && (y + 1) < _MAP->map.size())
				{
					if (_MAP->map.at(y-1).at(x) == 1 && _MAP->map.at(y + 1).at(x) == 0)
					{
						type = 2;
					}
					else if (_MAP->map.at(y - 1).at(x) == 0 && _MAP->map.at(y + 1).at(x) == 0)
					{
						type = 0;
					}
					else if (_MAP->map.at(y - 1).at(x) == 1 && _MAP->map.at(y + 1).at(x) == 1)
					{
						type = 1;
					}
					else if (_MAP->map.at(y - 1).at(x) == 0 && _MAP->map.at(y + 1).at(x) == 1)
					{
						type = 3;
					}
				}

				SDL_Rect srctemp = { 16 * type, 0, 16,16 };
				SDL_RenderCopy(_renderer, wall, &srctemp, &temp);
			}

		}
	}
	SDL_SetRenderTarget(_renderer, NULL);
	SDL_DestroyTexture(floor);
	SDL_DestroyTexture(wall);
	//SDL_DestroyTexture(randomobjects);
	return;
}