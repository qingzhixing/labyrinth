#include <game_map.h>
#include <core_error_code.h>
#include <utility>
#include <filesystem>
#include <debug_log.h>
#include <fstream>

using std::make_pair;
using std::pair;

static pair<MapData, GameCoreErrorCode> ReadMapData(std::ifstream &map_stream)
{
}

pair<GameMap, GameCoreErrorCode>
GameMap::ParseMapFile(const std::string &map_file_path)
{
	GameMap game_map;

	// Check The Map File Exists
	if (std::filesystem::exists(map_file_path) == false)
	{
		DebugLog(LogLevel::ERROR, "Map file not found: %s", map_file_path.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// Check The Map File Is Not A Directory
	if (std::filesystem::is_directory(map_file_path))
	{
		DebugLog(LogLevel::ERROR, "Map file is a directory: %s", map_file_path.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
	}

	auto game_map_stream = std::ifstream(map_file_path);
	if (game_map_stream.is_open() == false)
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file: %s", map_file_path.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	auto [map_data, read_error_code] = ReadMapData(game_map_stream);
	if (read_error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, read_error_code.toMessage());
		return make_pair(std::move(game_map), read_error_code);
	}
	game_map.map_data = map_data;
	game_map.lines = map_data.size();
	game_map.columns = map_data[0].size();

	return make_pair(std::move(game_map), GameCoreErrorCode::SUCCESS);
}