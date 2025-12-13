#include <game_map_extend.h>
#include <testkit.h>
#include <iostream>
#include <debug_log.h>

void PrintMap(const GameMapExtend &map)
{
	if (IsDebugLogNotEnabled())
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
	assert(map.PlacePlayerIfNeeded());
	assert(map.player_coordinate == Coordinate(0, 0));
}

UnitTest(GameMapExtend_PlacePlayerIfNeeded_InvalidMap)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::WALL, MapCellType::WALL},
					{MapCellType::WALL, MapCellType::WALL}};
	map.size = {2, 2};

	PrintMap(map);
	assert(!map.PlacePlayerIfNeeded());
}

UnitTest(GameMapExtend_MovePlayer_MoveToWall)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::WALL},
					{MapCellType::SPACE, MapCellType::SPACE}};
	map.size = {2, 2};

	PrintMap(map);
	assert(map.PlacePlayerIfNeeded());
	assert(map.player_coordinate == Coordinate(0, 0));

	// Move Player to (0, 1)
	auto result = map.MovePlayer(Direction::RIGHT);
	DebugLog(LogLevel::INFO, "Move Player to (0, 1) result: " + result.toMessage());
	PrintMap(map);

	assert(result == GameCoreErrorCode::MOVE_FAILED);
}

UnitTest(GameMapExtend_MovePlayer_MoveToSpace_MoveToNullSpace)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::WALL},
					{MapCellType::SPACE, MapCellType::SPACE}};
	map.size = {2, 2};

	PrintMap(map);
	assert(map.PlacePlayerIfNeeded());
	assert(map.player_coordinate == Coordinate(0, 0));

	// Move Player to (-1, 0)
	auto result = map.MovePlayer(Direction::UP);
	DebugLog(LogLevel::INFO, "Move Player to (-1, 0) result: " + result.toMessage());
	PrintMap(map);

	assert(result == GameCoreErrorCode::MOVE_FAILED);
}

UnitTest(GameMapExtend_MovePlayer_MoveToSpace)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::SPACE},
					{MapCellType::PLAYER, MapCellType::SPACE}};
	map.size = {2, 2};
	map.player_coordinate = Coordinate(1, 0);

	PrintMap(map);
	assert(map.PlacePlayerIfNeeded());
	assert(map.player_coordinate == Coordinate(1, 0));

	// Move Player to (1, 1)

	auto result = map.MovePlayer(Direction::RIGHT);
	DebugLog(LogLevel::INFO, "Move Player to (1, 1) result: " + result.toMessage());
	PrintMap(map);

	assert(result == GameCoreErrorCode::SUCCESS);
	assert(map.player_coordinate == Coordinate(1, 1));
	assert(map.map_data[1][1] == MapCellType::PLAYER);
	assert(map.map_data[1][0] == MapCellType::SPACE);
}

UnitTest(GameMapExtend_MovePlayer_MoveToDestination)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::SPACE},
					{MapCellType::PLAYER, MapCellType::DESTINATION}};
	map.size = {2, 2};
	map.player_coordinate = Coordinate(1, 0);

	PrintMap(map);
	assert(map.PlacePlayerIfNeeded());
	assert(map.player_coordinate == Coordinate(1, 0));

	// Move Player to (1, 1)
	auto result = map.MovePlayer(Direction::RIGHT);
	DebugLog(LogLevel::INFO, "Move Player to (1, 1) result: " + result.toMessage());
	PrintMap(map);

	assert(result == GameCoreErrorCode::SUCCESS);
	assert(map.player_coordinate == Coordinate(1, 1));
	assert(map.map_data[1][1] == MapCellType::PLAYER_AT_DESTINATION);
	assert(map.map_data[1][0] == MapCellType::SPACE);
}