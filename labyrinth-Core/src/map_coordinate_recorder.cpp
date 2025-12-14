#include "map_coordinate_recorder.h"
#include <debug_log.h>

bool MapCoordinateRecorder::IsPlayerCell(MapCellType cell_type)
{
	return cell_type == MapCellType::PLAYER ||
		   cell_type == MapCellType::PLAYER_AT_DESTINATION;
}

bool MapCoordinateRecorder::IsDestinationCell(MapCellType cell_type)
{
	return cell_type == MapCellType::DESTINATION ||
		   cell_type == MapCellType::PLAYER_AT_DESTINATION;
}

GameCoreErrorCode MapCoordinateRecorder::RecordPlayerIfNeeded(
	MapCellType cell_type, int line, int column)
{
	if (!IsPlayerCell(cell_type))
	{
		return GameCoreErrorCode::SUCCESS;
	}

	if (player_coordinate.IsValid())
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid map format: multiple players '0'/'W' found");
		return GameCoreErrorCode::MAP_MULTIPLE_PLAYER;
	}
	player_coordinate = Coordinate(line, column);
	DebugLog(
		LogLevel::DEBUG,
		"Player coordinate: %d, %d", line, column);

	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode MapCoordinateRecorder::RecordDestinationIfNeeded(
	MapCellType cell_type, int line, int column)
{
	if (!IsDestinationCell(cell_type))
	{
		return GameCoreErrorCode::SUCCESS;
	}
	if (destination.IsValid())
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid map format: multiple destinations '@'/'W' found");
		return GameCoreErrorCode::MAP_MULTIPLE_DESTINATION;
	}
	destination = Coordinate(line, column);
	DebugLog(
		LogLevel::DEBUG,
		"Destination coordinate: %d, %d",
		line, column);
	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode MapCoordinateRecorder::RecordCoordinates(
	MapCellType cell_type, int line, int column)
{
	auto player_error = RecordPlayerIfNeeded(cell_type, line, column);
	if (player_error != GameCoreErrorCode::SUCCESS)
	{
		return player_error;
	}

	auto destination_error =
		RecordDestinationIfNeeded(cell_type, line, column);
	if (destination_error != GameCoreErrorCode::SUCCESS)
	{
		return destination_error;
	}

	return GameCoreErrorCode::SUCCESS;
}