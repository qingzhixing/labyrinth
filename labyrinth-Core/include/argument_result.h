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
	bool validate = false;
};

struct ParsedResultWithErrorCode
{
	ParsedResult parsed_result{};
	ErrorCode error_code = ErrorCode::DEFAULT_ERROR_CODE;
};

struct ValidatedGameContext
{
	GameMapExtend game_map;
	std::string map_file_path{};
	Direction direction = Direction::INVALID;
	bool validate = {};
};

struct ValidatedGameContextWithErrorCode
{
	ValidatedGameContext validated_game_context{};
	ErrorCode error_code = ErrorCode::DEFAULT_ERROR_CODE;
};

#endif // ARG_RESULT_H
