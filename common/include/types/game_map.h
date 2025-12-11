#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <vector>
#include <string>
#include <types/core_error_code.h>
#include <types/map_size.h>
#include <types/map_cell.h>
#include <types/coordinate.h>
#include <game_info.h>

typedef std::vector<MapCellType> MapLine;
typedef std::vector<MapLine> MapData;

class GameMap
{
public:
	MapSize size;
	MapData map_data;
	Coordinate player_coordinate = INVALID_COORDINATE;
	Coordinate destination = INVALID_COORDINATE;
};
#endif // GAME_MAP_H