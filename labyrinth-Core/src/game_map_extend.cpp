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

GameCoreErrorCode GameMapExtend::MovePlayer(Direction direction)
{
	// TODO: Untested

	// 检查玩家是否可以移动到目标方向
	Coordinate target_coordinate =
		player_coordinate + DirectionToCoordinate(direction);

	if (!target_coordinate.IsValid())
	{
		return GameCoreErrorCode::MOVE_FAILED;
	}

	auto &target_cell =
		map_data[target_coordinate.line][target_coordinate.column];
	if (target_cell == MapCellType::WALL)
	{
		return GameCoreErrorCode::MOVE_FAILED;
	}

	// 移动玩家

	player_coordinate = target_coordinate;
	auto &current_cell =
		map_data[player_coordinate.line][player_coordinate.column];
	current_cell = MapCellType::SPACE;

	// 改变地图
	if (target_cell == MapCellType::SPACE)
	{
		target_cell = MapCellType::PLAYER;
	}
	else if (target_cell == MapCellType::DESTINATION)
	{
		target_cell = MapCellType::PLAYER_AT_DESTINATION;
	}
	return GameCoreErrorCode::SUCCESS;
}

Coordinate GameMapExtend::GetFirstLeftUpSpace() const
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

bool GameMapExtend::PlacePlayerIfNeeded()
{
	// TODO: Untested
	// 检查玩家是否需要被放置
	if (!player_coordinate.IsValid())
	{
		player_coordinate = GetFirstLeftUpSpace();
	}
	return player_coordinate.IsValid();
}