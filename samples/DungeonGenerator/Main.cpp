#include <conio.h>

#include "DungeonGenerator.h"

#include <random>
#include <chrono>

void PrintMap(std::vector<std::vector<int>> _intmap)
{
	for (size_t y = 0; y < _intmap.size(); y++)
	{
		for (size_t x = 0; x < _intmap.at(y).size(); x++)
		{
			printf("%i", _intmap.at(y).at(x));
		}
		printf("\n");
	}
	printf("\n");
}

#undef main
int main()
{
	srand((unsigned int)time(NULL));

	// create the map
	Level* map = new Level(glm::ivec2(75,50));

	//Add rooms and print
	DungeonGenerator::PopulateWithRooms(map, 11);
	PrintMap(map->map);

	// Connect the rooms with pathfinder and print
	DungeonGenerator::ConnectRooms(map);
	map->UpdateNodeMap();
	PrintMap(map->map);
	
	// cleanup
	delete map;
	return 0;
}