#pragma once
#ifndef PARSED_RESULT_H
#define PARSED_RESULT_H
#include <string>
#include <core_info.h>
#include <core_error_code.h>

struct ParsedResult
{
	std::string map_file{};
	std::string player_id{};
	std::string move_direction{};
};

typedef std::pair<ParsedResult, GameCoreErrorCode> ParsedResultWithErrorCode;

#endif // PARSED_RESULT_H