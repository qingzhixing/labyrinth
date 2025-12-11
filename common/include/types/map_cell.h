#pragma once
#ifndef MAP_CELL_H
#define MAP_CELL_H

enum class MapCellType : char
{
	SPACE = '.',
	WALL = '#',
	DESTINATION = '@',
	PLAYER = '0',
	INVALID = '?'
};

MapCellType GetMapCellType(char ch);

#endif // MAP_CELL_H
