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

// 函数声明
MapCellType GetMapCellType(char ch);
char GetMapCellChar(MapCellType type);

#endif // MAP_CELL_H