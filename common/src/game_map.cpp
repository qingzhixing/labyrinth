#include <game_map.h>
#include <types/core_error_code.h>
#include <utility>
#include <filesystem>
#include <debug_log.h>
#include <fstream>

using std::make_pair;
using std::make_tuple;
using std::move;
using std::pair;
using std::string;
using std::tuple;

MapCellType GetMapCellType(char ch)
{
	switch (ch)
	{
	case '#':
		return MapCellType::WALL;
	case '.':
		return MapCellType::SPACE;
	default:
		return MapCellType::INVALID;
	}
}

static pair<GameMap, GameCoreErrorCode> ReadMapData(std::ifstream &map_stream)
{
	int columns = 0;
	int line_index = 0;

	GameMap game_map;

	// Read The Map Data and Get Size
	string current_line_str;
	while (std::getline(map_stream, current_line_str))
	{
		line_index++;
		if (line_index > MAX_MAP_SIZE.lines)
		{
			DebugLog(LogLevel::ERROR, "Map too large: exceeds maximum lines %d", MAX_MAP_SIZE.lines);
			return make_pair(move(game_map), GameCoreErrorCode::MAP_TOO_LARGE);
		}

		if (columns == 0)
		{
			columns = current_line_str.length();
		}
		else if (columns != current_line_str.length())
		{
			DebugLog(LogLevel::ERROR, "Invalid map format: inconsistent line lengths");
			return make_pair(move(game_map), GameCoreErrorCode::INVALID_MAP_FORMAT);
		}
		else if (line_index > MAX_MAP_SIZE.columns)
		{
			DebugLog(LogLevel::ERROR, "Map too large: exceeds maximum columns %d", MAX_MAP_SIZE.columns);
			return make_pair(move(game_map), GameCoreErrorCode::MAP_TOO_LARGE);
		}

		MapLine map_line;
		for (auto &ch : current_line_str)
		{
			auto cell_type = GetMapCellType(ch);
			if (cell_type != MapCellType::INVALID)
			{
				map_line.push_back(cell_type);
				continue;
			}

			// 判断是否为player
			if (ch >= '0' && ch <= '9')
			{
				map_line.push_back(MapCellType::SPACE);
				Coordinate coord = {line_index - 1, static_cast<int>(map_line.size() - 1)};
				game_map.player_coordinates[ch - '0'] = coord;
				continue;
			}

			DebugLog(LogLevel::ERROR, "Invalid map format: unknown cell type '%c' at line %d", ch, line_index);
			return make_pair(move(game_map), GameCoreErrorCode::INVALID_MAP_FORMAT);
		}
		game_map.map_data.push_back(map_line);
	}
	game_map.size.lines = line_index;
	game_map.size.columns = columns;

	if (line_index == 0)
	{
		DebugLog(LogLevel::ERROR, "Invalid map format: empty map file");
		return make_pair(move(game_map), GameCoreErrorCode::INVALID_MAP_FORMAT);
	}

	return make_pair(move(game_map), GameCoreErrorCode::SUCCESS);
}

pair<GameMap, GameCoreErrorCode> ParseMapFile(const std::string &map_file_path)
{
	GameMap game_map;

	// Check The Map File Exists
	if (std::filesystem::exists(map_file_path) == false)
	{
		DebugLog(LogLevel::ERROR, "Map file not found: %s", map_file_path.c_str());
		return make_pair(move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// Check The Map File Is Not A Directory
	if (std::filesystem::is_directory(map_file_path))
	{
		DebugLog(LogLevel::ERROR, "Map file is a directory: %s", map_file_path.c_str());
		return make_pair(move(game_map), GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
	}

	auto game_map_stream = std::ifstream(map_file_path);
	if (game_map_stream.is_open() == false)
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file: %s", map_file_path.c_str());
		return make_pair(move(game_map), GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	GameCoreErrorCode read_map_error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;
	std::tie(game_map, read_map_error_code) = ReadMapData(game_map_stream);
	if (read_map_error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, read_map_error_code.toMessage());
		return make_pair(std::move(game_map), read_map_error_code);
	}

	return make_pair(move(game_map), GameCoreErrorCode::SUCCESS);
}