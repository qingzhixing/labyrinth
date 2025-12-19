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

ErrorCode MapCoordinateRecorder::RecordPlayerIfNeeded(
	MapCellType cell_type, int line, int column)
{
	if (!IsPlayerCell(cell_type))
	{
		return ErrorCode::SUCCESS;
	}

	// 已经有player_coordinate了
	if (player_coordinate.IsPositive())
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid map format: multiple players '0'/'W' found");
		return ErrorCode::MAP_MULTIPLE_PLAYER;
	}
	player_coordinate = Coordinate(line, column);
	DebugLog(
		LogLevel::DEBUG,
		"Player coordinate: %d, %d", line, column);

	return ErrorCode::SUCCESS;
}

ErrorCode MapCoordinateRecorder::RecordDestinationIfNeeded(
	MapCellType cell_type, int line, int column)
{
	if (!IsDestinationCell(cell_type))
	{
		return ErrorCode::SUCCESS;
	}
	if (destination.IsPositive())
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid map format: multiple destinations '@'/'W' found");
		return ErrorCode::MAP_MULTIPLE_DESTINATION;
	}
	destination = Coordinate(line, column);
	DebugLog(
		LogLevel::DEBUG,
		"Destination coordinate: %d, %d",
		line, column);
	return ErrorCode::SUCCESS;
}

ErrorCode MapCoordinateRecorder::RecordCoordinates(
	MapCellType cell_type, int line, int column)
{
	auto player_error = RecordPlayerIfNeeded(cell_type, line, column);
	if (player_error != ErrorCode::SUCCESS)
	{
		return player_error;
	}

	auto destination_error =
		RecordDestinationIfNeeded(cell_type, line, column);
	if (destination_error != ErrorCode::SUCCESS)
	{
		return destination_error;
	}

	return ErrorCode::SUCCESS;
}