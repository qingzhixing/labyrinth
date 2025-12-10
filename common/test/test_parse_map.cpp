#include <game_map.h>
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
					<< "01" << endl
					<< "23" << endl
					<< "45" << endl
					<< "67" << endl
					<< "89" << endl
					<< "#." << endl;
	game_map_stream.close();

	auto [game_map, error_code] = ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseMapFile_Invalid_MapFormat_EmptyFile)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream.close();

	auto [game_map, error_code] = ParseMapFile(map_file);

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
					<< "01" << endl
					<< "23" << endl
					<< "45" << endl
					<< "67" << endl
					<< "89" << endl
					<< "#." << endl;
	game_map_stream.close();

	auto [game_map, error_code] = ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::INVALID_MAP_FORMAT);
}

UnitTest(TestParseMapFile_Invalid_MapFormat_UnknownCellType)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream << ".." << endl
					<< ".." << endl
					<< "#." << endl
					<< "0 " << endl
					<< "23" << endl
					<< "45" << endl
					<< "67" << endl
					<< "8)" << endl
					<< "#." << endl;
	game_map_stream.close();

	auto [game_map, error_code] = ParseMapFile(map_file);

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

	auto [game_map, error_code] = ParseMapFile(map_file);

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

	auto [game_map, error_code] = ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::MAP_TOO_LARGE);
}

UnitTest(TestParseMapFile_Invalid_NotFound)
{
	std::string map_file = "non_existent_" + std::to_string(rand()) + "_map.txt";

	auto [game_map, error_code] = ParseMapFile(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(TesParseMapFile_Invalid_IsDirectory)
{
	std::string map_file = "test_directory_" + std::to_string(rand());

	// Create a directory
	std::filesystem::create_directory(map_file);

	// Validate the map file
	auto [game_map, error_code] = ParseMapFile(map_file);

	// Remove the directory
	std::filesystem::remove(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
}