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

/**
 * @brief 地图验证器 - 负责地图格式和内容的验证
 */
class MapValidator
{
public:
	static bool ValidateSize(int lines, int columns)
	{
		if (lines > MAX_MAP_SIZE.lines)
		{
			DebugLog(LogLevel::ERROR,
					 "Map too large: exceeds maximum lines %d",
					 MAX_MAP_SIZE.lines);
			return false;
		}
		if (columns > MAX_MAP_SIZE.columns)
		{
			DebugLog(LogLevel::ERROR,
					 "Map too large: exceeds maximum columns %d",
					 MAX_MAP_SIZE.columns);
			return false;
		}
		return true;
	}

	static bool ValidateLineLengths(int expected_length, int actual_length, int line_index)
	{
		if (expected_length != 0 && expected_length != actual_length)
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: inconsistent line lengths at line %d",
					 line_index);
			return false;
		}
		return true;
	}

	static bool ValidateCellType(MapCellType cell_type, char ch, int line_index)
	{
		if (cell_type == MapCellType::INVALID)
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: unknown cell type '%c' at line %d",
					 ch, line_index);
			return false;
		}
		return true;
	}

	static bool ValidateMapNotEmpty(int total_lines)
	{
		if (total_lines == 0)
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: empty map file");
			return false;
		}
		return true;
	}

	static bool ValidateHasDestination(const Coordinate &destination)
	{
		if (destination == INVALID_COORDINATE)
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: no destination '@' found");
			return false;
		}
		return true;
	}
};

/**
 * @brief 坐标记录器 - 负责记录玩家和目的地的坐标
 */
class CoordinateRecorder
{
private:
	Coordinate player_coordinate = INVALID_COORDINATE;
	Coordinate destination = INVALID_COORDINATE;

	static bool IsPlayerCell(MapCellType cell_type)
	{
		return cell_type == MapCellType::PLAYER ||
			   cell_type == MapCellType::PLAYER_AT_DESTINATION;
	}

	static bool IsDestinationCell(MapCellType cell_type)
	{
		return cell_type == MapCellType::DESTINATION ||
			   cell_type == MapCellType::PLAYER_AT_DESTINATION;
	}

public:
	GameCoreErrorCode
	RecordPlayerIfNeeded(MapCellType cell_type, int line, int column)
	{
		if (!IsPlayerCell(cell_type))
		{
			return GameCoreErrorCode::SUCCESS;
		}

		if (player_coordinate.IsValid())
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: multiple players '0'/'W' found");
			return GameCoreErrorCode::MAP_MULTIPLE_PLAYER;
		}
		player_coordinate = Coordinate(line, column);
		DebugLog(LogLevel::DEBUG,
				 "Player coordinate: %d, %d", line, column);

		return GameCoreErrorCode::SUCCESS;
	}

	GameCoreErrorCode
	RecordDestinationIfNeeded(MapCellType cell_type, int line, int column)
	{
		if (IsDestinationCell(cell_type))
		{
			return GameCoreErrorCode::SUCCESS;
		}
		if (destination.IsValid())
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: multiple destinations '@'/'W' found");
			return GameCoreErrorCode::MAP_MULTIPLE_DESTINATION;
		}
		destination = Coordinate(line, column);
		DebugLog(LogLevel::DEBUG,
				 "Destination coordinate: %d, %d",
				 line, column);
		return GameCoreErrorCode::SUCCESS;
	}

	GameCoreErrorCode
	RecordCoordinates(MapCellType cell_type, int line, int column)
	{
		auto player_error = RecordPlayerIfNeeded(cell_type, line, column);
		if (player_error != GameCoreErrorCode::SUCCESS)
		{
			return player_error;
		}

		auto destination_error =
			RecordDestinationIfNeeded(cell_type, line, column);
		if (destination_error != GameCoreErrorCode::SUCCESS)
		{
			return destination_error;
		}

		return GameCoreErrorCode::SUCCESS;
	}

	Coordinate GetPlayerCoordinate() const { return player_coordinate; }
	Coordinate GetDestination() const { return destination; }

	bool HasPlayer() const { return player_coordinate.IsValid(); }
	bool HasDestination() const { return destination.IsValid(); }
};

/**
 * @brief 地图行处理器 - 负责处理单行地图数据
 */
class MapLineProcessor
{
public:
	static pair<MapLine, GameCoreErrorCode>
	ProcessLine(
		const string &line_str,
		int line_index,
		CoordinateRecorder &recorder)
	{
		MapLine map_line;

		for (size_t column = 0; column < line_str.length(); column++)
		{
			char ch = line_str[column];
			auto cell_type = GetMapCellType(ch);

			// 验证单元格类型
			if (!MapValidator::ValidateCellType(cell_type, ch, line_index))
			{
				return make_pair(
					MapLine(),
					GameCoreErrorCode::INVALID_MAP_FORMAT);
			}

			map_line.push_back(cell_type);

			// 记录坐标
			auto record_error = recorder.RecordCoordinates(
				cell_type, line_index - 1, static_cast<int>(column));
			if (record_error != GameCoreErrorCode::SUCCESS)
			{
				return make_pair(MapLine(), record_error);
			}
		}

		return make_pair(
			move(map_line),
			GameCoreErrorCode::SUCCESS);
	}
};

/**
 * @brief 地图构建器 - 负责构建最终的地图对象
 */
class MapBuilder
{
public:
	static pair<GameMapExtend, GameCoreErrorCode> BuildFinalMap(
		const std::vector<MapLine> &map_data,
		const CoordinateRecorder &recorder,
		int total_lines,
		int total_columns)
	{

		GameMapExtend game_map;
		game_map.map_data = map_data;
		game_map.size.lines = total_lines;
		game_map.size.columns = total_columns;
		game_map.player_coordinate = recorder.GetPlayerCoordinate();
		game_map.destination = recorder.GetDestination();

		// 最终验证
		if (!MapValidator::ValidateMapNotEmpty(total_lines))
		{
			return make_pair(
				move(game_map),
				GameCoreErrorCode::INVALID_MAP_FORMAT);
		}

		if (!MapValidator::ValidateHasDestination(game_map.destination))
		{
			return make_pair(
				move(game_map),
				GameCoreErrorCode::MAP_NO_DESTINATION);
		}

		// 检查地图连通性
		if (!game_map.CheckMapConnectivity())
		{
			DebugLog(LogLevel::ERROR, "Invalid map format: map is not fully connected");
			return make_pair(
				move(game_map),
				GameCoreErrorCode::INVALID_MAP_FORMAT);
		}

		game_map.PlacePlayer();

		return make_pair(
			move(game_map),
			GameCoreErrorCode::SUCCESS);
	}
};

/**
 * @brief 读取地图数据 - 从文件流中读取地图数据并构建 GameMapExtend 对象
 * @param map_stream 输入文件流，用于读取地图数据
 * @return pair<GameMapExtend, GameCoreErrorCode> 包含构建的地图对象和错误码的对
 */
static pair<GameMapExtend, GameCoreErrorCode>
ReadMapData(std::ifstream &map_stream)
{
	std::vector<MapLine> map_data;
	CoordinateRecorder recorder;
	int line_index = 0;
	int expected_columns = 0;

	string current_line_str;
	while (std::getline(map_stream, current_line_str))
	{
		line_index++;

		// 验证地图大小
		if (!MapValidator::ValidateSize(
				line_index, static_cast<int>(current_line_str.length())))
		{
			return make_pair(
				GameMapExtend(),
				GameCoreErrorCode::MAP_TOO_LARGE);
		}

		// 验证行长度一致性
		if (!MapValidator::ValidateLineLengths(
				expected_columns,
				static_cast<int>(current_line_str.length()),
				line_index))
		{
			return make_pair(
				GameMapExtend(),
				GameCoreErrorCode::MAP_INCONSISTENT_LINE);
		}

		// 处理单行数据
		auto line_result = MapLineProcessor::ProcessLine(
			current_line_str,
			line_index,
			recorder);
		if (line_result.second != GameCoreErrorCode::SUCCESS)
		{
			return make_pair(
				GameMapExtend(),
				line_result.second);
		}

		map_data.push_back(move(line_result.first));

		// 设置期望的列数（只在第一行设置）
		if (expected_columns == 0)
		{
			expected_columns = static_cast<int>(current_line_str.length());
		}
	}

	// 构建最终的地图对象
	return MapBuilder::BuildFinalMap(
		map_data,
		recorder,
		line_index,
		expected_columns);
}

pair<GameMapExtend, GameCoreErrorCode>
GameMapExtend::ParseMapFile(const std::string &map_file_path)
{
	GameMapExtend game_map;

	// Check The Map File Exists
	if (std::filesystem::exists(map_file_path) == false)
	{
		DebugLog(LogLevel::ERROR,
				 "Map file not found: %s",
				 map_file_path.c_str());
		return make_pair(
			move(game_map),
			GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// Check The Map File Is Not A Directory
	if (std::filesystem::is_directory(map_file_path))
	{
		DebugLog(LogLevel::ERROR,
				 "Map file is a directory: %s", map_file_path.c_str());
		return make_pair(
			move(game_map),
			GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
	}

	auto game_map_stream = std::ifstream(map_file_path);
	if (game_map_stream.is_open() == false)
	{
		DebugLog(LogLevel::ERROR,
				 "Failed to open map file: %s", map_file_path.c_str());
		return make_pair(
			move(game_map),
			GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	GameCoreErrorCode read_map_error_code =
		GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 读取地图数据
	std::tie(game_map, read_map_error_code) =
		ReadMapData(game_map_stream);

	if (read_map_error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR,
				 read_map_error_code.toMessage());
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