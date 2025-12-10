#pragma once
#ifndef ARG_RESULT_H
#define ARG_RESULT_H
#include <string>
#include <core_info.h>
#include <core_error_code.h>
#include <fstream>
#include <string>
#include <game_map.h>

struct ParsedResult
{
	std::string mapFile{};
	std::string playerID{};
	std::string move_direction{};
};

typedef std::pair<ParsedResult, GameCoreErrorCode> ParsedResultWithErrorCode;

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	INVALID
};

struct ValidatedGameContext
{
	GameMap game_map;						  // map_file的文件描述符
	int playerID;							  // 转换为整数的player_id
	Direction direction = Direction::INVALID; // 移动方向的枚举
};

typedef std::pair<ValidatedGameContext, GameCoreErrorCode> ValidatedGameContextWithErrorCode;

#endif // ARG_RESULT_H
