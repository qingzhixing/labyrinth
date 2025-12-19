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

	GameMapExtend &operator=(const GameMapExtend &other);

	ErrorCode MovePlayer(Direction direction);

	/**
	 * @brief 查找地图上第一个左上空格子的坐标
	 *
	 * @return Coordinate 第一个左上空格子的坐标
	 */
	Coordinate GetFirstLeftUpSpace() const;

	/**
	 * @brief 在地图上放置玩家(如果玩家坐标在地图上并没有指出)
	 *
	 * @return true 玩家被成功放置
	 * @return false 玩家未被放置(玩家坐标在地图上已经指出)
	 */
	bool PlacePlayerIfNeeded();

	ErrorCode WriteBackMap(const std::string &map_file_path) const;
};

#endif // GAME_MAP_EXTEND_H