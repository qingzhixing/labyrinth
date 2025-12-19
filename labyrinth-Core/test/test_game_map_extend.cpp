#include <game_map_extend.h>
#include <testkit.h>
#include <iostream>
#include <debug_log.h>
#include <fstream>
#include <filesystem>

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

	assert(result == ErrorCode::MOVE_FAILED);
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

	assert(result == ErrorCode::MOVE_FAILED);
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

	assert(result == ErrorCode::SUCCESS);
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

	assert(result == ErrorCode::SUCCESS);
	assert(map.player_coordinate == Coordinate(1, 1));
	assert(map.map_data[1][1] == MapCellType::PLAYER_AT_DESTINATION);
	assert(map.map_data[1][0] == MapCellType::SPACE);
}

UnitTest(GameMapExtend_WriteBackMap)
{
	GameMapExtend map;
	map.map_data = {{MapCellType::SPACE, MapCellType::WALL},
					{MapCellType::PLAYER, MapCellType::DESTINATION}};
	map.size = {2, 2};

	PrintMap(map);
	// Write Back Map
	auto map_path = "test_map_" + std::to_string(rand()) + ".txt";
	auto result = map.WriteBackMap(map_path);

	// Read the map back
	auto map_file = std::ifstream(map_path);
	if (!map_file.is_open())
	{
		DebugLog(LogLevel::ERROR, "Read Map file failed: " + map_path);
		assert(false);
	}
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(map_file, line))
	{
		lines.push_back(line);
	}

	// Close the file stream
	map_file.close();

	std::filesystem::remove(map_path);

	// Check the map data
	assert(lines.size() == map.size.lines);
	for (int i = 0; i < map.size.lines; i++)
	{
		for (int j = 0; j < map.size.columns; j++)
		{
			assert(lines[i][j] == GetMapCellChar(map.map_data[i][j]));
		}
	}
	assert(result == ErrorCode::SUCCESS);
}