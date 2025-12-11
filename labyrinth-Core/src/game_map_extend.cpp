#include <game_map_extend.h>
#include <filesystem>
#include <debug_log.h>
#include <utility>
#include <string>
#include <fstream>

using std::make_pair;
using std::move;
using std::pair;
using std::string;

static pair<GameMap, GameCoreErrorCode> ReadMapData(std::ifstream &map_stream)
{
	int columns = 0;
	int line_index = 0;

	GameMapExtend game_map;

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
			return make_pair(move(game_map), GameCoreErrorCode::MAP_INCONSISTENT_LINE);
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
			if (cell_type == MapCellType::INVALID)
			{
				DebugLog(LogLevel::ERROR, "Invalid map format: unknown cell type '%c' at line %d", ch, line_index);
				return make_pair(move(game_map), GameCoreErrorCode::INVALID_MAP_FORMAT);
			}
			map_line.push_back(cell_type);

			bool set_player = (cell_type == MapCellType::PLAYER || cell_type == MapCellType::PLAYER_AT_DESTINATION);
			bool set_destination = (cell_type == MapCellType::DESTINATION || cell_type == MapCellType::PLAYER_AT_DESTINATION);

			// 记录destination坐标
			if (set_destination)
			{
				DebugLog(LogLevel::DEBUG, "Destination coordinate: %d, %d", line_index - 1, static_cast<int>(map_line.size() - 1));
				if (game_map.destination.IsValid())
				{
					DebugLog(LogLevel::ERROR, "Invalid map format: multiple destinations '@'/'W' found");
					return make_pair(move(game_map), GameCoreErrorCode::MAP_MULTIPLE_DESTINATION);
				}
				game_map.destination = Coordinate(line_index - 1, static_cast<int>(map_line.size() - 1));
			}

			// 记录player坐标
			if (set_player)
			{
				DebugLog(LogLevel::DEBUG, "Player coordinate: %d, %d", line_index - 1, static_cast<int>(map_line.size() - 1));
				if (game_map.player_coordinate.IsValid())
				{
					DebugLog(LogLevel::ERROR, "Invalid map format: multiple players '0'/'W' found");
					return make_pair(move(game_map), GameCoreErrorCode::MAP_MULTIPLE_PLAYER);
				}
				game_map.player_coordinate = Coordinate(line_index - 1, static_cast<int>(map_line.size() - 1));
			}
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

	// 检查是否有destination
	if (game_map.destination == INVALID_COORDINATE)
	{
		DebugLog(LogLevel::ERROR, "Invalid map format: no destination '@' found");
		return make_pair(move(game_map), GameCoreErrorCode::MAP_NO_DESTINATION);
	}

	// 检查地图连通性
	if (!game_map.CheckMapConnectivity())
	{
		DebugLog(LogLevel::ERROR, "Invalid map format: map is not fully connected");
		return make_pair(move(game_map), GameCoreErrorCode::INVALID_MAP_FORMAT);
	}

	game_map.PlacePlayer();

	return make_pair(move(game_map), GameCoreErrorCode::SUCCESS);
}

pair<GameMapExtend, GameCoreErrorCode> GameMapExtend::ParseMapFile(const std::string &map_file_path)
{
	GameMapExtend game_map;

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

bool GameMapExtend::CheckMapConnectivity() const
{
	// TODO:Unimplemented
	return true;
}

void GameMapExtend::PlacePlayer()
{
	// TODO:Unimplemented
}
