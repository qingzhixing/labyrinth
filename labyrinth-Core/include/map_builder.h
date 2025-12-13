#pragma once
#ifndef MAP_BUILDER_H
#define MAP_BUILDER_H

#include <types/game_map.h>
#include <coordinate_recorder.h>
#include <map_validator.h>
#include <debug_log.h>
#include <types/core_error_code.h>
#include <game_map_extend.h>

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
			DebugLog(
				LogLevel::ERROR,
				"Invalid map format: map is not fully connected");
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

#endif // MAP_BUILDER_H
