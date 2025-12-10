#include <game_map.h>
#include <testkit.h>
#include <fstream>
#include <filesystem>
#include <debug_log.h>

UnitTest(TestParseMapFile_Valid)
{
	std::string mapFile = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream game_map_stream(mapFile);
	game_map_stream.close();

	auto [game_map, error_code] = GameMap::ParseMapFile(mapFile);

	// Delete the map file
	std::remove(mapFile.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseMapFile_Invalid_NotFound)
{
	std::string mapFile = "non_existent_" + std::to_string(rand()) + "_map.txt";

	auto [game_map, error_code] = GameMap::ParseMapFile(mapFile);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(TesParseMapFile_Invalid_IsDirectory)
{
	std::string mapFile = "test_directory_" + std::to_string(rand());

	// Create a directory
	std::filesystem::create_directory(mapFile);

	// Validate the map file
	auto [game_map, error_code] = GameMap::ParseMapFile(mapFile);

	// Remove the directory
	std::filesystem::remove(mapFile);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
}