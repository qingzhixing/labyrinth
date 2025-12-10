#include <game_map.h>
#include <testkit.h>
#include <fstream>
#include <filesystem>
#include <debug_log.h>

UnitTest(TestParseMapFile_Valid)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(map_file);
	game_map_stream.close();

	auto [game_map, error_code] = GameMap::ParseMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseMapFile_Invalid_NotFound)
{
	std::string map_file = "non_existent_" + std::to_string(rand()) + "_map.txt";

	auto [game_map, error_code] = GameMap::ParseMapFile(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(TesParseMapFile_Invalid_IsDirectory)
{
	std::string map_file = "test_directory_" + std::to_string(rand());

	// Create a directory
	std::filesystem::create_directory(map_file);

	// Validate the map file
	auto [game_map, error_code] = GameMap::ParseMapFile(map_file);

	// Remove the directory
	std::filesystem::remove(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
}