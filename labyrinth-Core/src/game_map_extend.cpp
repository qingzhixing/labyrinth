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

void GameMapExtend::PlacePlayerIfNeeded()
{
	// TODO: Untested
	if (!player_coordinate.IsValid())
	{
		player_coordinate = GetFirstLeftUpSpace();
	}
}