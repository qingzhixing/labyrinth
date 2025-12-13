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
		return MapCellType::PLAYER;
	case 'W':
		return MapCellType::PLAYER_AT_DESTINATION;
	default:
		return MapCellType::INVALID;
	}
}

char GetMapCellChar(MapCellType type)
{
	return static_cast<char>(type);
}