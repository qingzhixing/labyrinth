#include <arg_validate.h>
#include <debug_log.h>
#include <stdexcept>
#include <unistd.h>
#include <filesystem>

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

pair<int, GameCoreErrorCode> ValidatePlayerID(const std::string &player_id)
{
	int player_id_int = NO_PLAYER_ID;
	if (player_id.empty())
	{
		DebugLog(LogLevel::INFO, "Player ID is empty");
		// 没有ID我们需要在代码中自动放置, Player ID为0
		return make_pair(NO_PLAYER_ID, GameCoreErrorCode::SUCCESS);
	}
	try
	{
		player_id_int = std::stoi(player_id);
	}
	catch (const std::invalid_argument &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be a number: %s", player_id.c_str());
		return make_pair(NO_PLAYER_ID, GameCoreErrorCode::INVALID_PLAYER_ID);
	}
	catch (const std::out_of_range &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID out of int range: %s", player_id.c_str());
		return make_pair(NO_PLAYER_ID, GameCoreErrorCode::INVALID_PLAYER_ID);
	}

	if (player_id_int < 0 || player_id_int > MAX_PLAYER_COUNT)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be greater than 0 and less than %d: %d", MAX_PLAYER_COUNT, player_id_int);
		return make_pair(player_id_int, GameCoreErrorCode::INVALID_PLAYER_ID);
	}
	return make_pair(player_id_int, GameCoreErrorCode::SUCCESS);
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

	// --player
	std::tie(validated_context.player_id, error_code) = ValidatePlayerID(parsed_result.player_id);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --map
	std::tie(validated_context.game_map, error_code) = ParseMapFile(parsed_result.map_file);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	error_code = GameCoreErrorCode::SUCCESS;
	return make_pair(validated_context, error_code);
}