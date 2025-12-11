#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <core_error_code.h>
#include <game_info.h>

enum class MapCellType : char
{
	SPACE = '.',
	WALL = '#',
	INVALID = '?'
};

struct MapSize
{
	int lines, columns;
};

struct Coordinate
{
	int line, column;
};

inline const MapSize MAX_MAP_SIZE = {100, 100};

MapCellType GetMapCellType(char ch);

typedef std::vector<MapCellType> MapLine;
typedef std::vector<MapLine> MapData;

class GameMap
{
public:
	MapSize size;
	MapData map_data;
	Coordinate player_coordinates[MAX_PLAYER_COUNT + 1];
};

/**
 * @brief 解析地图文件，构造GameMap对象并返回错误码
 *
 * @param file_path
 * @return std::pair<GameMap, GameCoreErrorCode> returns constructed GameMap and error code
 */
std::pair<GameMap, GameCoreErrorCode> ParseMapFile(const std::string &file_path);

#endif // GAME_MAP_H