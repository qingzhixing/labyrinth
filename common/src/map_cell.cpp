#include <types/map_cell.h>

MapCellType GetMapCellType(char ch)
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
		return MapCellType::PLAYER_0;
	default:
		return MapCellType::INVALID;
	}
}