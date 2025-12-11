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
	GameCoreErrorCode MovePlayer(Direction direction);

	/**
	 * @brief 解析地图文件，构造GameMap对象并返回错误码
	 *
	 * @param file_path
	 * @return std::pair<GameMap, GameCoreErrorCode> returns constructed GameMap and error code
	 */
	static std::pair<GameMapExtend, GameCoreErrorCode> ParseMapFile(const std::string &file_path);

	/**
	 * @brief 检查地图连通性,保证每个非墙体的格子都能到达
	 *
	 * @return true 如果地图是连通的
	 * @return false 如果地图不是连通的
	 */
	bool CheckMapConnectivity() const;

	/**
	 * @brief 在地图上放置玩家(如果玩家坐标在地图上并没有指出)
	 *
	 */
	void PlacePlayer();
};

#endif // GAME_MAP_EXTEND_H