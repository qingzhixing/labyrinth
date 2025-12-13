#pragma once
#ifndef MAP_CELL_H
#define MAP_CELL_H

enum class MapCellType : char
{
	SPACE = '.',
	WALL = '#',
	DESTINATION = '@',
	PLAYER = '0',
	PLAYER_AT_DESTINATION = 'W',
	INVALID = '?'
};

inline MapCellType GetMapCellType(char ch)
{
	switch (ch)
	{
	case '#':
		return MapCellType::WALL;
	case '.':
		return MapCellType::SPACE;
	case '@':
		return MapCellType::DESTINATION;
	case '0':
		return MapCellType::PLAYER;
	case 'W':
		return MapCellType::PLAYER_AT_DESTINATION;
	default:
		return MapCellType::INVALID;
	}
}

inline char GetMapCellChar(MapCellType type)
{
	return static_cast<char>(type);
}

#endif // MAP_CELL_H
