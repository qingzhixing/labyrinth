#pragma once
#ifndef MAP_VALIDATOR_H
#define MAP_VALIDATOR_H

#include <types/map_cell.h>
#include <types/coordinate.h>
#include <types/map_size.h>
#include <types/game_map.h>
#include <game_map_extend.h>
#include <debug_log.h>
#include <queue>

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
				"Invalid map format: inconsistent row lengths at row %d",
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
				"Invalid map format: unknown cell type '%c' at row %d",
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

	/**
	 * @brief 检查地图连通性,保证每个非墙体的格子都能到达
	 *
	 * @return true 如果地图是连通的
	 * @return false 如果地图不是连通的
	 */
	static bool ValidateMapConnectivity(GameMapExtend &game_map)
	{
		bool checked[game_map.size.lines][game_map.size.columns] = {};

		std::queue<Coordinate> bfs_queue;

		// 从左上角开始BFS
		bfs_queue.push(game_map.GetFirstLeftUpSpace());
		checked[bfs_queue.front().row][bfs_queue.front().column] = true;
		while (!bfs_queue.empty())
		{
			auto current = bfs_queue.front();
			bfs_queue.pop();

			// 检查四个方向
			for (
				Direction dir : {
					Direction::UP, Direction::DOWN,
					Direction::LEFT, Direction::RIGHT})
			{
				Coordinate next = current + DirectionToCoordinate(dir);
				// Invalid Coordinate
				if (next.row < 0 || next.row >= game_map.size.lines ||
					next.column < 0 || next.column >= game_map.size.columns)
				{
					continue;
				}
				// Unmatched
				if (game_map.map_data[next.row][next.column] != MapCellType::WALL &&
					!checked[next.row][next.column])
				{
					bfs_queue.push(next);
					checked[next.row][next.column] = true;
				}
			}
		}

		// 遍历查看每个SPACE是否连通
		for (int row = 0; row < game_map.size.lines; row++)
		{
			for (int column = 0; column < game_map.size.columns; column++)
			{
				if (game_map.map_data[row][column] == MapCellType::SPACE &&
					!checked[row][column])
				{
					return false;
				}
			}
		}

		return true;
	}
};

#endif // MAP_VALIDATOR_H
