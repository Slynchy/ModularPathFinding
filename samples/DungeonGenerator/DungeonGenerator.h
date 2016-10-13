#pragma once

#include <vector>
#include <glm\glm.hpp>

struct NODE;

struct ROOM
{
	glm::ivec2 pos;
	glm::ivec2 size;
};

struct SDL_Texture;
struct SDL_Renderer;

class Level
{
protected:
	void ClearMap();
	void ClearMap(glm::ivec2 _size);
private:
public:
	std::vector<std::vector<int>> map;
	std::vector<std::vector<NODE*>> nmap;
	std::vector<ROOM> rooms;
	SDL_Texture* texture;
	Level(glm::ivec2 _size);
	void UpdateNodeMap();
	void Reset();
};

class DungeonGenerator
{
	protected:
	private:
		DungeonGenerator()
		{
			// private constructor
		}
	public:
		static void DungeonGenerator::PlaceRoom(Level* _MAP, glm::ivec2 _pos, glm::ivec2 _size, int _type);
		static void DungeonGenerator::PopulateWithRooms(Level* _MAP, unsigned int _roomcount);
		static void DungeonGenerator::ConnectRooms(Level* _MAP);
		static void DungeonGenerator::GenerateTexture(SDL_Renderer* _renderer, Level* _MAP);
};