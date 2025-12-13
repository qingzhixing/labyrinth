#pragma once
#ifndef COORDINATE_RECORDER_H
#define COORDINATE_RECORDER_H

#include <types/coordinate.h>
#include <types/map_cell.h>
#include <types/core_error_code.h>
#include <debug_log.h>

/**
 * @brief 坐标记录器 - 负责记录玩家和目的地的坐标
 */
class MapCoordinateRecorder
{
private:
	Coordinate player_coordinate = INVALID_COORDINATE;
	Coordinate destination = INVALID_COORDINATE;

	static bool IsPlayerCell(MapCellType cell_type)
	{
		return cell_type == MapCellType::PLAYER ||
			   cell_type == MapCellType::PLAYER_AT_DESTINATION;
	}

	static bool IsDestinationCell(MapCellType cell_type)
	{
		return cell_type == MapCellType::DESTINATION ||
			   cell_type == MapCellType::PLAYER_AT_DESTINATION;
	}

public:
	GameCoreErrorCode
	RecordPlayerIfNeeded(MapCellType cell_type, int line, int column)
	{
		if (!IsPlayerCell(cell_type))
		{
			return GameCoreErrorCode::SUCCESS;
		}

		if (player_coordinate.IsValid())
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: multiple players '0'/'W' found");
			return GameCoreErrorCode::MAP_MULTIPLE_PLAYER;
		}
		player_coordinate = Coordinate(line, column);
		DebugLog(LogLevel::DEBUG,
				 "Player coordinate: %d, %d", line, column);

		return GameCoreErrorCode::SUCCESS;
	}

	GameCoreErrorCode
	RecordDestinationIfNeeded(MapCellType cell_type, int line, int column)
	{
		if (!IsDestinationCell(cell_type))
		{
			return GameCoreErrorCode::SUCCESS;
		}
		if (destination.IsValid())
		{
			DebugLog(LogLevel::ERROR,
					 "Invalid map format: multiple destinations '@'/'W' found");
			return GameCoreErrorCode::MAP_MULTIPLE_DESTINATION;
		}
		destination = Coordinate(line, column);
		DebugLog(LogLevel::DEBUG,
				 "Destination coordinate: %d, %d",
				 line, column);
		return GameCoreErrorCode::SUCCESS;
	}

	GameCoreErrorCode
	RecordCoordinates(MapCellType cell_type, int line, int column)
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

	Coordinate GetPlayerCoordinate() const { return player_coordinate; }
	Coordinate GetDestination() const { return destination; }

	bool HasPlayer() const { return player_coordinate.IsValid(); }
	bool HasDestination() const { return destination.IsValid(); }
};

#endif // COORDINATE_RECORDER_H
