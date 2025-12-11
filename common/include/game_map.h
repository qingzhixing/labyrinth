#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <types/core_error_code.h>
#include <game_info.h>

enum class MapCellType : char
{
	SPACE = '.',
	WALL = '#',
	INVALID = '?'
};

MapCellType GetMapCellType(char ch);

struct MapSize
{
	int lines, columns;
	MapSize(int lines = 0, int columns = 0) : lines(lines), columns(columns) {}
	bool operator==(const MapSize &other) const
	{
		return lines == other.lines && columns == other.columns;
	}
};
inline const MapSize MAX_MAP_SIZE = {100, 100};

struct Coordinate
{
	int line, column;
	Coordinate(int line = -1, int column = -1) : line(line), column(column) {}
	bool operator==(const Coordinate &other) const
	{
		return line == other.line && column == other.column;
	}
};

MapCellType GetMapCellType(char ch);

typedef std::vector<MapCellType> MapLine;
typedef std::vector<MapLine> MapData;

class GameMap
{
public:
	MapSize size;
	MapData map_data;
	Coordinate player_coordinates[MAX_PLAYER_COUNT + 1];
};
#endif // GAME_MAP_H