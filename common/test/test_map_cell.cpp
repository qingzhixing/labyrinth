#include <types/map_cell.h>
#include <testkit.h>

UnitTest(TestGetMapCellType_Valid)
{
	assert(GetMapCellType('#') == MapCellType::WALL);
	assert(GetMapCellType('.') == MapCellType::SPACE);
	assert(GetMapCellType('?') == MapCellType::INVALID);
	assert(GetMapCellType('X') == MapCellType::INVALID);
	assert(GetMapCellType('@') == MapCellType::DESTINATION);
	assert(GetMapCellType('0') == MapCellType::PLAYER);
}