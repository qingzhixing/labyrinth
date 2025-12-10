#include <game_map.h>
#include <core_error_code.h>
#include <utility>
#include <filesystem>
#include <debug_log.h>
#include <fstream>

using std::make_pair;
using std::pair;

pair<GameMap, GameCoreErrorCode> GameMap::ParseMapFile(const std::string &mapFilePath)
{
	GameMap game_map;

	// Check The Map File Exists
	if (std::filesystem::exists(mapFilePath) == false)
	{
		DebugLog(LogLevel::ERROR, "Map file not found: %s", mapFilePath.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// Check The Map File Is Not A Directory
	if (std::filesystem::is_directory(mapFilePath))
	{
		DebugLog(LogLevel::ERROR, "Map file is a directory: %s", mapFilePath.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
	}

	auto game_map_stream = std::ofstream(mapFilePath);
	if (game_map_stream.is_open() == false)
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file: %s", mapFilePath.c_str());
		return make_pair(std::move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// TODO:继续解析 Map 文件内容

	return make_pair(std::move(game_map), GameCoreErrorCode::SUCCESS);
}