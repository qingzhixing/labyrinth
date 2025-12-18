#pragma once
#ifndef ARG_RESULT_H
#define ARG_RESULT_H
#include <string>
#include <core_info.h>
#include <types/error_code.h>
#include <types/direction.h>
#include <fstream>
#include <string>
#include <game_map_extend.h>

struct ParsedResult
{
	std::string map_file{};
	std::string direction{};
};

struct ParsedResultWithErrorCode
{
	ParsedResult parsed_result{};
	ErrorCode error_code = ErrorCode::DEFAULT_ERROR_CODE;
};

struct ValidatedGameContext
{
	GameMapExtend game_map;					  // map_file的文件描述符
	Direction direction = Direction::INVALID; // 移动方向的枚举
};

struct ValidatedGameContextWithErrorCode
{
	ValidatedGameContext validated_game_context{};
	ErrorCode error_code = ErrorCode::DEFAULT_ERROR_CODE;
};

#endif // ARG_RESULT_H
