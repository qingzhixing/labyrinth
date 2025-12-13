#pragma once
#ifndef MAP_VALIDATOR_H
#define MAP_VALIDATOR_H

#include <types/map_cell.h>
#include <types/coordinate.h>
#include <types/map_size.h>
#include <debug_log.h>

/**
 * @brief 地图验证器 - 负责地图格式和内容的验证
 */
class MapValidator
{
public:
	static bool ValidateSize(int lines, int columns)
	{
		if (lines > MAX_MAP_SIZE.lines)
		{
			DebugLog(
				LogLevel::ERROR,
				"Map too large: exceeds maximum lines %d",
				MAX_MAP_SIZE.lines);
			return false;
		}
		if (columns > MAX_MAP_SIZE.columns)
		{
			DebugLog(
				LogLevel::ERROR,
				"Map too large: exceeds maximum columns %d",
				MAX_MAP_SIZE.columns);
			return false;
		}
		return true;
	}

	static bool ValidateLineLengths(
		int expected_length,
		int actual_length,
		int line_index)
	{
		if (expected_length != 0 && expected_length != actual_length)
		{
			DebugLog(
				LogLevel::ERROR,
				"Invalid map format: inconsistent line lengths at line %d",
				line_index);
			return false;
		}
		return true;
	}

	static bool ValidateCellType(MapCellType cell_type, char ch, int line_index)
	{
		if (cell_type == MapCellType::INVALID)
		{
			DebugLog(
				LogLevel::ERROR,
				"Invalid map format: unknown cell type '%c' at line %d",
				ch, line_index);
			return false;
		}
		return true;
	}

	static bool ValidateMapNotEmpty(int total_lines)
	{
		if (total_lines == 0)
		{
			DebugLog(
				LogLevel::ERROR,
				"Invalid map format: empty map file");
			return false;
		}
		return true;
	}

	static bool ValidateHasDestination(const Coordinate &destination)
	{
		if (destination == INVALID_COORDINATE)
		{
			DebugLog(
				LogLevel::ERROR,
				"Invalid map format: no destination '@' found");
			return false;
		}
		return true;
	}
};

#endif // MAP_VALIDATOR_H
