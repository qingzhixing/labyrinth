#pragma once
#ifndef GAME_MAP_EXTEND_H
#define GAME_MAP_EXTEND_H

#include <types/game_map.h>
#include <types/direction.h>

class GameMapExtend : public GameMap
{
public:
	GameMapExtend() : GameMap() {}
	GameMapExtend(const GameMap &other) : GameMap(other) {}
	GameCoreErrorCode MovePlayer(int player_id, Direction direction);

	/**
	 * @brief 解析地图文件，构造GameMap对象并返回错误码
	 *
	 * @param file_path
	 * @return std::pair<GameMap, GameCoreErrorCode> returns constructed GameMap and error code
	 */
	static std::pair<GameMapExtend, GameCoreErrorCode> ParseMapFile(const std::string &file_path);
};

#endif // GAME_MAP_EXTEND_H