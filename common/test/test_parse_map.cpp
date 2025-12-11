#include <game_map.h>
#include <testkit.h>
#include <fstream>
#include <filesystem>
#include <debug_log.h>

using std::endl;

UnitTest(TestGetMapCellType_Valid)
{
	assert(GetMapCellType('#') == MapCellType::WALL);
	assert(GetMapCellType('.') == MapCellType::SPACE);
	assert(GetMapCellType('?') == MapCellType::INVALID);
}