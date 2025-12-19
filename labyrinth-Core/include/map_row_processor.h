#pragma once
#ifndef MAP_ROW_PROCESSOR_H
#define MAP_ROW_PROCESSOR_H

#include <map_validator.h>
#include <map_coordinate_recorder.h>
#include <types/game_map.h>

/**
 * @brief 地图行处理器 - 负责处理单行地图数据
 */
class MapRowProcessor
{
public:
	static std::pair<MapRow, ErrorCode>
	ProcessRow(
		const std::string &row_str,
		int row_index,
		MapCoordinateRecorder &recorder);
};

#endif // MAP_ROW_PROCESSOR_H
