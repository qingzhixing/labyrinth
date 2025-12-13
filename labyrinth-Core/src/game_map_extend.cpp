#include <game_map_extend.h>
#include <filesystem>
#include <debug_log.h>
#include <utility>
#include <string>
#include <fstream>
#include <queue>

#include <map_validator.h>
#include <coordinate_recorder.h>
#include <map_line_processor.h>

/**
 * @brief 地图构建器 - 负责构建最终的地图对象
 */
class MapBuilder
{
public:
	static std::pair<GameMapExtend, GameCoreErrorCode> BuildFinalMap(
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
			return std::make_pair(
				std::move(game_map),
				GameCoreErrorCode::INVALID_MAP_FORMAT);
		}

		if (!MapValidator::ValidateHasDestination(game_map.destination))
		{
			return std::make_pair(
				std::move(game_map),
				GameCoreErrorCode::MAP_NO_DESTINATION);
		}

		// 检查地图连通性
		if (!game_map.CheckMapConnectivity())
		{
			DebugLog(LogLevel::ERROR, "Invalid map format: map is not fully connected");
			return std::make_pair(
				std::move(game_map),
				GameCoreErrorCode::INVALID_MAP_FORMAT);
		}

		game_map.PlacePlayerIfNeeded();

		return std::make_pair(
			std::move(game_map),
			GameCoreErrorCode::SUCCESS);
	}
};

/**
 * @brief 读取地图数据 - 从文件流中读取地图数据并构建 GameMapExtend 对象
 * @param map_stream 输入文件流，用于读取地图数据
 * @return pair<GameMapExtend, GameCoreErrorCode> 包含构建的地图对象和错误码的对
 */
static std::pair<GameMapExtend, GameCoreErrorCode>
ReadMapData(std::ifstream &map_stream)
{
	std::vector<MapLine> map_data;
	CoordinateRecorder recorder;
	int line_index = 0;
	int expected_columns = 0;

	std::string current_line_str;
	while (std::getline(map_stream, current_line_str))
	{
		line_index++;

		// 验证地图大小
		if (!MapValidator::ValidateSize(
				line_index, static_cast<int>(current_line_str.length())))
		{
			return std::make_pair(
				GameMapExtend(),
				GameCoreErrorCode::MAP_TOO_LARGE);
		}

		// 验证行长度一致性
		if (!MapValidator::ValidateLineLengths(
				expected_columns,
				static_cast<int>(current_line_str.length()),
				line_index))
		{
			return std::make_pair(
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
			return std::make_pair(
				GameMapExtend(),
				line_result.second);
		}

		map_data.push_back(std::move(line_result.first));

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

std::pair<GameMapExtend, GameCoreErrorCode>
GameMapExtend::ParseMapFile(const std::string &map_file_path)
{
	GameMapExtend game_map;

	// Check The Map File Exists
	if (std::filesystem::exists(map_file_path) == false)
	{
		DebugLog(LogLevel::ERROR,
				 "Map file not found: %s",
				 map_file_path.c_str());
		return std::make_pair(
			std::move(game_map),
			GameCoreErrorCode::MAP_FILE_NOT_FOUND);
	}

	// Check The Map File Is Not A Directory
	if (std::filesystem::is_directory(map_file_path))
	{
		DebugLog(LogLevel::ERROR,
				 "Map file is a directory: %s", map_file_path.c_str());
		return std::make_pair(
			std::move(game_map),
			GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
	}

	auto game_map_stream = std::ifstream(map_file_path);
	if (game_map_stream.is_open() == false)
	{
		DebugLog(LogLevel::ERROR,
				 "Failed to open map file: %s", map_file_path.c_str());
		return std::make_pair(
			std::move(game_map),
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
		return std::make_pair(std::move(game_map), read_map_error_code);
	}

	return std::make_pair(std::move(game_map), GameCoreErrorCode::SUCCESS);
}

Coordinate GameMapExtend::FindFirstLeftUpSpace() const
{
	// TODO: Untested
	// 从左上角开始遍历地图
	for (int line = 0; line < size.lines; line++)
	{
		for (int column = 0; column < size.columns; column++)
		{
			if (map_data[line][column] == MapCellType::SPACE)
			{
				return Coordinate(line, column);
			}
		}
	}
	return INVALID_COORDINATE;
}

bool GameMapExtend::CheckMapConnectivity() const
{
	// TODO: Untested
	bool checked[size.lines][size.columns] = {};
	std::queue<Coordinate> bfs_queue;
	// 从左上角开始BFS
	bfs_queue.push(FindFirstLeftUpSpace());
	checked[bfs_queue.front().line][bfs_queue.front().column] = true;
	while (!bfs_queue.empty())
	{
		auto current = bfs_queue.front();
		bfs_queue.pop();

		// 检查四个方向
		for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT})
		{
			Coordinate next = current + DirectionToCoordinate(dir);
			// Invalid Coordinate
			if (next.line < 0 || next.line >= size.lines || next.column < 0 || next.column >= size.columns)
			{
				continue;
			}
			// Unmatched
			if (map_data[next.line][next.column] != MapCellType::WALL &&
				!checked[next.line][next.column])
			{
				bfs_queue.push(next);
				checked[next.line][next.column] = true;
			}
		}
	}

	// 遍历查看每个SPACE是否连通
	for (int line = 0; line < size.lines; line++)
	{
		for (int column = 0; column < size.columns; column++)
		{
			if (map_data[line][column] == MapCellType::SPACE &&
				!checked[line][column])
			{
				return false;
			}
		}
	}

	return true;
}

void GameMapExtend::PlacePlayerIfNeeded()
{
	// TODO: Untested
	if (!player_coordinate.IsValid())
	{
		player_coordinate = FindFirstLeftUpSpace();
	}
}