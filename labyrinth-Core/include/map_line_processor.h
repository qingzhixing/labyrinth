#pragma once
#ifndef MAP_LINE_PROCESSOR_H
#define MAP_LINE_PROCESSOR_H

#include <map_validator.h>
#include <coordinate_recorder.h>
#include <types/game_map.h>

/**
 * @brief 地图行处理器 - 负责处理单行地图数据
 */
class MapLineProcessor
{
public:
	static std::pair<MapLine, GameCoreErrorCode>
	ProcessLine(
		const std::string &line_str,
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

#endif // MAP_LINE_PROCESSOR_H
