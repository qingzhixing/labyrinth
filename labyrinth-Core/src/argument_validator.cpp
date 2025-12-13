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

GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsed_result)
{
	bool missing_parameters = false;
	if (parsed_result.map_file.empty())
	{
		missing_parameters = true;
	}
	if (parsed_result.move_direction.empty())
	{
		missing_parameters = true;
	}
	if (missing_parameters)
	{
		return GameCoreErrorCode::MISSING_PARAMETERS;
	}
	return GameCoreErrorCode::SUCCESS;
}

pair<Direction, GameCoreErrorCode> ValidateMoveDirection(const std::string &move_direction)
{
	Direction direction = Direction::INVALID;
	if (move_direction == "up")
	{
		direction = Direction::UP;
	}
	else if (move_direction == "down")
	{
		direction = Direction::DOWN;
	}
	else if (move_direction == "left")
	{
		direction = Direction::LEFT;
	}
	else if (move_direction == "right")
	{
		direction = Direction::RIGHT;
	}
	else
	{
		DebugLog(LogLevel::ERROR, "Invalid move direction: %s", move_direction.c_str());
		return std::make_pair(Direction::INVALID, GameCoreErrorCode::INVALID_MOVE_DIRECTION);
	}
	return std::make_pair(direction, GameCoreErrorCode::SUCCESS);
}

ValidatedGameContextWithErrorCode ValidateParsedResult(const ParsedResult &parsed_result)
{
	// 检查参数是否合法

	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;
	ValidatedGameContext validated_context{};

	// 检查缺失参数
	error_code = CheckMissingParameters(parsed_result);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --move
	std::tie(validated_context.direction, error_code) = ValidateMoveDirection(parsed_result.move_direction);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --map
	std::tie(validated_context.game_map, error_code) = MapParser::ParseMapFile(parsed_result.map_file);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	error_code = GameCoreErrorCode::SUCCESS;
	return make_pair(validated_context, error_code);
}