#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <core_error_code.h>

class GameMap
{
public:
	int lines, columns;
	std::vector<std::vector<char>> map_data;

public:
	/**
	 * @brief 解析地图文件，构造GameMap对象并返回错误码
	 *
	 * @param filePath
	 * @return std::pair<GameMap, GameCoreErrorCode> returns constructed GameMap and error code
	 */
	static std::pair<GameMap, GameCoreErrorCode> ParseMapFile(const std::string &filePath);
};

#endif // GAME_MAP_H