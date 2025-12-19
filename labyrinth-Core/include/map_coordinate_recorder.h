#pragma once
#ifndef COORDINATE_RECORDER_H
#define COORDINATE_RECORDER_H

#include <types/coordinate.h>
#include <types/map_cell.h>
#include <types/error_code.h>
#include <debug_log.h>

class MapCoordinateRecorderTest;

/**
 * @brief 坐标记录器 - 负责记录玩家和目的地的坐标
 */
class MapCoordinateRecorder
{
private:
	Coordinate player_coordinate = INVALID_COORDINATE;
	Coordinate destination = INVALID_COORDINATE;

	static bool IsPlayerCell(MapCellType cell_type);
	static bool IsDestinationCell(MapCellType cell_type);

public:
	ErrorCode
	RecordPlayerIfNeeded(MapCellType cell_type, int row, int column);

	ErrorCode
	RecordDestinationIfNeeded(MapCellType cell_type, int row, int column);

	ErrorCode
	RecordCoordinates(MapCellType cell_type, int row, int column);

	Coordinate GetPlayerCoordinate() const { return player_coordinate; }
	Coordinate GetDestination() const { return destination; }

	bool HasPlayer() const { return player_coordinate.IsPositive(); }
	bool HasDestination() const { return destination.IsPositive(); }

	friend class MapCoordinateRecorderTest;
};

#endif // COORDINATE_RECORDER_H