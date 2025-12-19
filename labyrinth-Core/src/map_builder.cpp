#include <map_builder.h>
#include <map_validator.h>
#include <debug_log.h>
#include <game_map_extend.h>

std::pair<GameMapExtend, ErrorCode> MapBuilder::BuildFinalMap(
	const std::vector<MapRow> &map_data,
	const MapCoordinateRecorder &recorder,
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
			ErrorCode::INVALID_MAP_FORMAT);
	}

	if (!MapValidator::ValidateHasDestination(game_map.destination))
	{
		return std::make_pair(
			std::move(game_map),
			ErrorCode::MAP_NO_DESTINATION);
	}

	// 检查地图连通性
	if (!MapValidator::ValidateMapConnectivity(game_map))
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid map format: map is not fully connected");
		return std::make_pair(
			std::move(game_map),
			ErrorCode::INVALID_MAP_FORMAT);
	}

	game_map.PlacePlayerIfNeeded();

	return std::make_pair(
		std::move(game_map),
		ErrorCode::SUCCESS);
}