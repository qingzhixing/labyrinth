#include <game_map.h>
#include <types/core_error_code.h>
#include <utility>
#include <filesystem>
#include <debug_log.h>
#include <fstream>

using std::make_pair;
using std::make_tuple;
using std::move;
using std::pair;
using std::string;
using std::tuple;
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