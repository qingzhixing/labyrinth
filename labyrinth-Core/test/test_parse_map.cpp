#include <game_map_extend.h>
#include <testkit.h>
#include <fstream>
#include <filesystem>
#include <debug_log.h>

using std::endl;

UnitTest(TestParseMapFile_Valid)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".." << endl
					<< ".." << endl
					<< "#." << endl
					<< "0." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< "#@" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::SUCCESS);

	// Check for player coordinates
	auto &player_coords = game_map.player_coordinate;
	assert(player_coords == Coordinate(3, 0));

	// Check map size
	assert(game_map.size == MapSize(9, 2));

	// Check map data
	assert(game_map.map_data.size() == 9);
	assert(game_map.map_data[0][0] == MapCellType::SPACE);
	assert(game_map.map_data[0][1] == MapCellType::SPACE);
	assert(game_map.map_data[1][0] == MapCellType::SPACE);
	assert(game_map.map_data[1][1] == MapCellType::SPACE);
	assert(game_map.map_data[2][0] == MapCellType::WALL);
	assert(game_map.map_data[2][1] == MapCellType::SPACE);
	assert(game_map.map_data[3][0] == MapCellType::PLAYER);
	assert(game_map.map_data[3][1] == MapCellType::SPACE);
	assert(game_map.map_data[4][0] == MapCellType::SPACE);
	assert(game_map.map_data[4][1] == MapCellType::SPACE);
	assert(game_map.map_data[5][0] == MapCellType::SPACE);
	assert(game_map.map_data[5][1] == MapCellType::SPACE);
	assert(game_map.map_data[6][0] == MapCellType::SPACE);
	assert(game_map.map_data[6][1] == MapCellType::SPACE);
	assert(game_map.map_data[7][0] == MapCellType::SPACE);
	assert(game_map.map_data[7][1] == MapCellType::SPACE);
	assert(game_map.map_data[8][0] == MapCellType::WALL);
	assert(game_map.map_data[8][1] == MapCellType::DESTINATION);
	assert(game_map.destination == Coordinate(8, 1));
}

UnitTest(TestParseMapFile_Valid_PlayerAtDestination)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".." << endl
					<< ".W" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::SUCCESS);
	assert(game_map.player_coordinate == game_map.destination);
}

UnitTest(TestParseMapFile_Invalid_MultiplePlayer)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << "0." << endl
					<< ".0" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_MULTIPLE_PLAYER);
}

UnitTest(TestParseMapFile_Invalid_MultiplePlayer_PlayerAtDestination)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << "0." << endl
					<< ".W" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_MULTIPLE_PLAYER);
}

UnitTest(TestParseMapFile_Invalid_MultipleDestination_PlayerAtDestination)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".@" << endl
					<< ".W" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_MULTIPLE_DESTINATION);
}

UnitTest(TestParseMapFile_Invalid_MultipleDestination)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".@" << endl
					<< ".@" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_MULTIPLE_DESTINATION);
}

UnitTest(TestParseMapFile_Invalid_MapFormat_EmptyFile)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::INVALID_MAP_FORMAT);
}

UnitTest(TestParseMapFile_Invalid_MapFormat_InvalidLineLength)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".." << endl
					<< ".." << endl
					<< "#............." << endl
					<< "0." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< "#." << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_INCONSISTENT_LINE);
}

UnitTest(TestParseMapFile_Invalid_MapFormat_UnknownCellType)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".." << endl
					<< ".." << endl
					<< "#." << endl
					<< "0." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< ".." << endl
					<< "#}" << endl;
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::INVALID_MAP_FORMAT);
}

UnitTest(TestParseMapFile_Invalid_MapSize_TooMuchLines)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	for (int i = 0; i < MAX_MAP_SIZE.lines + 1; i++)
	{
		game_map_stream << ".." << endl;
	}
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_TOO_LARGE);
}

UnitTest(TestParseMapFile_Invalid_MapSize_TooMuchColumns)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	for (int i = 0; i < MAX_MAP_SIZE.columns + 1; i++)
	{
		game_map_stream << ".." << endl;
	}
	game_map_stream.close();

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_TOO_LARGE);
}

UnitTest(TestParseMapFile_Invalid_NotFound)
{
	std::string map_file = "non_existent_" + std::to_string(rand()) + "_map.txt";

	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(TesParseMapFile_Invalid_IsDirectory)
{
	std::string map_file = "test_directory_" + std::to_string(rand());

	// Create a directory
	std::filesystem::create_directory(map_file);

	// Validate the map file
	auto [game_map, error_code] = GameMapExtend::ParseMapFile(map_file);

	// Remove the directory
	std::filesystem::remove(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
}