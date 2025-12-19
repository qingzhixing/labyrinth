#include <game_map_extend.h>
#include <filesystem>
#include <debug_log.h>
#include <utility>
#include <string>
#include <fstream>
#include <queue>

#include <map_validator.h>
#include <map_coordinate_recorder.h>
#include <map_line_processor.h>
#include <map_builder.h>

GameMapExtend &GameMapExtend::operator=(const GameMapExtend &other)
{
	if (this != &other)
	{
		GameMap::operator=(other);
	}
	return *this;
}

ErrorCode
GameMapExtend::MovePlayer(Direction direction)
{

	// 检查玩家是否可以移动到目标方向
	Coordinate target_coordinate =
		player_coordinate + DirectionToCoordinate(direction);

	if (!target_coordinate.IsValid())
	{
		return ErrorCode::MOVE_FAILED;
	}

	auto &target_cell =
		map_data[target_coordinate.line][target_coordinate.column];
	if (target_cell == MapCellType::WALL)
	{
		return ErrorCode::MOVE_FAILED;
	}

	// 清空当前玩家位置
	auto &current_cell =
		map_data[player_coordinate.line][player_coordinate.column];
	current_cell = MapCellType::SPACE;

	// 移动玩家
	player_coordinate = target_coordinate;

	// 改变地图
	if (target_cell == MapCellType::SPACE)
	{
		target_cell = MapCellType::PLAYER;
	}
	else if (target_cell == MapCellType::DESTINATION)
	{
		target_cell = MapCellType::PLAYER_AT_DESTINATION;
	}

	return ErrorCode::SUCCESS;
}

Coordinate GameMapExtend::GetFirstLeftUpSpace() const
{
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

bool GameMapExtend::PlacePlayerIfNeeded()
{
	// 检查玩家是否需要被放置
	if (!player_coordinate.IsValid())
	{
		player_coordinate = GetFirstLeftUpSpace();
	}
	return player_coordinate.IsValid();
}

ErrorCode GameMapExtend::WriteBackMap(const std::string &map_file_path) const
{
	// 遍历地图,写入数据
	// 打开文件流
	std::fstream map_file(map_file_path, std::ios::out);
	if (!map_file.is_open())
	{
		return ErrorCode::MAP_FILE_OPEN_FAILED;
	}

	// 写入地图数据
	for (const auto &line : map_data)
	{
		for (const auto &cell : line)
		{
			map_file << GetMapCellChar(cell);
		}
		map_file << '\n';
	}

	// 关闭文件流
	map_file.close();
	return ErrorCode::SUCCESS;
}
