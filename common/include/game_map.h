#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <core_error_code.h>

enum class MapCellType : char
{
	SPACE = '.',
	WALL = '#',
	PLAYER_0 = '0',
	PLAYER_1 = '1',
	PLAYER_2 = '2',
	PLAYER_3 = '3',
	PLAYER_4 = '4',
	PLAYER_5 = '5',
	PLAYER_6 = '6',
	PLAYER_7 = '7',
	PLAYER_8 = '8',
	PLAYER_9 = '9',
	INVALID = '?'
};

struct MapSize
{
	int lines, columns;
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
};

/**
 * @brief 解析地图文件，构造GameMap对象并返回错误码
 *
 * @param file_path
 * @return std::pair<GameMap, GameCoreErrorCode> returns constructed GameMap and error code
 */
std::pair<GameMap, GameCoreErrorCode> ParseMapFile(const std::string &file_path);

#endif // GAME_MAP_H