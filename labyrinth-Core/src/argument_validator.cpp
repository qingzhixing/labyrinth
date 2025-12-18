#include <argument_validator.h>
#include <types/direction.h>
#include <debug_log.h>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <filesystem>
#include <map_parser.h>

using std::make_pair;
using std::pair;
using std::string;

ErrorCode
CheckMissingParameters(const ParsedResult &parsed_result)
{
	bool missing_parameters = false;
	if (parsed_result.map_file.empty())
	{
		missing_parameters = true;
	}
	if (parsed_result.direction.empty())
	{
		missing_parameters = true;
	}
	if (missing_parameters)
	{
		return ErrorCode::MISSING_PARAMETERS;
	}
	return ErrorCode::SUCCESS;
}

pair<Direction, ErrorCode>
ValidateMoveDirection(const std::string &direction_str)
{
	Direction direction = Direction::INVALID;
	if (direction_str == "up")
	{
		direction = Direction::UP;
	}
	else if (direction_str == "down")
	{
		direction = Direction::DOWN;
	}
	else if (direction_str == "left")
	{
		direction = Direction::LEFT;
	}
	else if (direction_str == "right")
	{
		direction = Direction::RIGHT;
	}
	else
	{
		DebugLog(
			LogLevel::ERROR,
			"Invalid move direction: %s",
			direction_str.c_str());
		return std::make_pair(
			Direction::INVALID,
			ErrorCode::INVALID_MOVE_DIRECTION);
	}
	return std::make_pair(
		direction,
		ErrorCode::SUCCESS);
}

ValidatedGameContextWithErrorCode
ValidateParsedResult(const ParsedResult &parsed_result)
{
	ErrorCode error_code =
		ErrorCode::DEFAULT_ERROR_CODE;
	ValidatedGameContext validated_context{};

	// 检查缺失参数
	error_code = CheckMissingParameters(parsed_result);
	if (error_code != ErrorCode::SUCCESS)
	{
		return {
			.validated_game_context = validated_context,
			.error_code = error_code};
	}

	// --move
	std::tie(
		validated_context.direction,
		error_code) =
		ValidateMoveDirection(parsed_result.direction);
	if (error_code != ErrorCode::SUCCESS)
	{
		return {
			.validated_game_context = validated_context,
			.error_code = error_code};
	}

	// --map
	std::tie(
		validated_context.game_map,
		error_code) =
		MapParser::ParseMapFile(
			parsed_result.map_file);
	if (error_code != ErrorCode::SUCCESS)
	{
		return {
			.validated_game_context = validated_context,
			.error_code = error_code};
	}

	error_code = ErrorCode::SUCCESS;
	return {
		.validated_game_context = validated_context,
		.error_code = error_code};
}