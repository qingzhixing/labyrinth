#include <arg_validate.h>
#include <debug_log.h>
#include <stdexcept>
#include <unistd.h>
#include <filesystem>

using std::make_pair;
using std::pair;
using std::string;

GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsedResult)
{
	bool missing_parameters = false;
	if (parsedResult.mapFile.empty())
	{
		missing_parameters = true;
	}
	if (parsedResult.move_direction.empty())
	{
		missing_parameters = true;
	}
	if (parsedResult.playerID.empty())
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

pair<int, GameCoreErrorCode> ValidatePlayerID(const std::string &playerID)
{
	int player_id_int = 114514;
	try
	{
		player_id_int = std::stoi(playerID);
	}
	catch (const std::invalid_argument &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be a number: %s", playerID.c_str());
		return make_pair(-1, GameCoreErrorCode::INVALID_PLAYER_ID);
	}
	catch (const std::out_of_range &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID out of int range: %s", playerID.c_str());
		return make_pair(-1, GameCoreErrorCode::INVALID_PLAYER_ID);
	}

	if (player_id_int < 0 || player_id_int > MAX_PLAYER_COUNT)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be greater than 0 and less than %d: %d", MAX_PLAYER_COUNT, player_id_int);
		return make_pair(player_id_int, GameCoreErrorCode::INVALID_PLAYER_ID);
	}
	return make_pair(player_id_int, GameCoreErrorCode::SUCCESS);
}

ValidatedGameContextWithErrorCode ValidateParsedResult(const ParsedResult &parsedResult)
{
	// 检查参数是否合法

	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;
	ValidatedGameContext validated_context{};

	// 检查缺失参数
	error_code = CheckMissingParameters(parsedResult);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --move
	std::tie(validated_context.direction, error_code) = ValidateMoveDirection(parsedResult.move_direction);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --player
	std::tie(validated_context.playerID, error_code) = ValidatePlayerID(parsedResult.playerID);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	// --map
	std::tie(validated_context.game_map, error_code) = GameMap::ParseMapFile(parsedResult.mapFile);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return make_pair(validated_context, error_code);
	}

	error_code = GameCoreErrorCode::SUCCESS;
	return make_pair(validated_context, error_code);
}