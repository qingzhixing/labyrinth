#pragma once
#ifndef MAP_LINE_PROCESSOR_H
#define MAP_LINE_PROCESSOR_H

#include <map_validator.h>
#include <map_coordinate_recorder.h>
#include <types/game_map.h>

/**
 * @brief 地图行处理器 - 负责处理单行地图数据
 */
class MapLineProcessor
{
public:
	static std::pair<MapLine, ErrorCode>
	ProcessLine(
		const std::string &line_str,
		int line_index,
		MapCoordinateRecorder &recorder);
};

#endif // MAP_LINE_PROCESSOR_H
