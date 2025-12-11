#pragma once
#ifndef ARG_RESULT_H
#define ARG_RESULT_H
#include <string>
#include <core_info.h>
#include <types/core_error_code.h>
#include <types/direction.h>
#include <fstream>
#include <string>
#include <game_map_extend.h>

struct ParsedResult
{
	std::string map_file{};
	std::string player_id{};
	std::string move_direction{};
};

typedef std::pair<ParsedResult, GameCoreErrorCode> ParsedResultWithErrorCode;

inline int NO_PLAYER_ID = -1;

struct ValidatedGameContext
{
	GameMapExtend game_map;					  // map_file的文件描述符
	int player_id = NO_PLAYER_ID;			  // 转换为整数的player_id
	Direction direction = Direction::INVALID; // 移动方向的枚举
};

typedef std::pair<ValidatedGameContext, GameCoreErrorCode> ValidatedGameContextWithErrorCode;

#endif // ARG_RESULT_H
