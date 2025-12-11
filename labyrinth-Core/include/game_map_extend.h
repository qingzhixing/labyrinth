#pragma once
#ifndef GAME_MAP_EXTEND_H
#define GAME_MAP_EXTEND_H

#include <game_map.h>
#include <types/direction.h>

class GameMapExtend : public GameMap
{
public:
	GameMapExtend() : GameMap() {}
	GameMapExtend(const GameMap &other) : GameMap(other) {}

	GameCoreErrorCode MovePlayer(int player_id, Direction direction);
};

#endif // GAME_MAP_EXTEND_H