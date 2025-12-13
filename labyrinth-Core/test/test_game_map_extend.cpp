#include <game_map_extend.h>
#include <testkit.h>
#include <iostream>
#include <debug_log.h>

void PrintMap(const GameMapExtend &map)
{
	if (!IsDebugLogNotEnabled())
	{
		return;
	}
	// Print Map Size
	std::cout << "Map Size: " << map.size.lines << " x " << map.size.columns << std::endl;
	for (const auto &line : map.map_data)
	{
		for (const auto &cell : line)
		{
			std::cout << GetMapCellChar(cell) << " ";
		}
		std::cout << std::endl;
	}
}

UnitTest(GameMapExtend_PlacePlayerIfNeeded_ValidMap)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::WALL},
					{MapCellType::SPACE, MapCellType::SPACE}};
	map.size = {2, 2};

	PrintMap(map);
	map.PlacePlayerIfNeeded();
}

UnitTest(GameMapExtend_PlacePlayerIfNeeded_InvalidMap)
{
	// Invalid Map
	GameMapExtend map;
	map.map_data = {{MapCellType::WALL, MapCellType::WALL},
					{MapCellType::WALL, MapCellType::WALL}};
	map.size = {2, 2};

	PrintMap(map);
	assert(!map.PlacePlayerIfNeeded());
}