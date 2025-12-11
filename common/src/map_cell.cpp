#include <types/map_cell.h>

MapCellType GetMapCellType(char ch)
{
	switch (ch)
	{
	case '#':
		return MapCellType::WALL;
	case '.':
		return MapCellType::SPACE;
	default:
		return MapCellType::INVALID;
	}
}