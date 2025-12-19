#pragma once
#ifndef MAP_BUILDER_H
#define MAP_BUILDER_H

#include <types/game_map.h>
#include <map_coordinate_recorder.h>
#include <map_validator.h>
#include <debug_log.h>
#include <types/error_code.h>
#include <game_map_extend.h>

/**
 * @brief 地图构建器 - 负责构建最终的地图对象
 */
class MapBuilder
{
public:
	static std::pair<GameMapExtend, ErrorCode> BuildFinalMap(
		const std::vector<MapRow> &map_data,
		const MapCoordinateRecorder &recorder,
		int total_lines,
		int total_columns);
};

#endif // MAP_BUILDER_H