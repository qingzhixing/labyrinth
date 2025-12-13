#pragma once
#ifndef MAP_VALIDATOR_H
#define MAP_VALIDATOR_H

#include <types/map_cell.h>
#include <types/coordinate.h>

/**
 * @brief 地图验证器 - 负责地图格式和内容的验证
 */
class MapValidator
{
public:
	static bool ValidateSize(int lines, int columns);

	static bool ValidateLineLengths(
		int expected_length,
		int actual_length,
		int line_index);

	static bool ValidateCellType(MapCellType cell_type, char ch, int line_index);

	static bool ValidateMapNotEmpty(int total_lines);

	static bool ValidateHasDestination(const Coordinate &destination);
};

#endif // MAP_VALIDATOR_H
