#include <arg_validate.h>
#include <debug_log.h>
#include <stdexcept>

GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsedResult)
{
	bool missing_parameters = false;
	if (parsedResult.map_file.empty())
	{
		missing_parameters = true;
	}
	if (parsedResult.move_direction.empty())
	{
		missing_parameters = true;
	}
	if (parsedResult.player_id.empty())
	{
		missing_parameters = true;
	}
	if (missing_parameters)
	{
		return GameCoreErrorCode::MISSING_PARAMETERS;
	}
	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode ValidateMoveDirection(const std::string &move_direction)
{
	if (move_direction != "up" && move_direction != "down" && move_direction != "left" && move_direction != "right")
	{
		return GameCoreErrorCode::INVALID_MOVE_DIRECTION;
	}
	return GameCoreErrorCode::SUCCESS;
}
GameCoreErrorCode ValidatePlayerID(const std::string &player_id)
{
	int player_id_int = -1;
	try
	{
		player_id_int = std::stoi(player_id);
	}
	catch (const std::invalid_argument &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be a number: %s", player_id.c_str());
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}
	catch (const std::out_of_range &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID out of int range: %s", player_id.c_str());
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}

	if (player_id_int < 0 || player_id_int > MAX_PLAYER_COUNT)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be greater than 0 and less than %d: %d", MAX_PLAYER_COUNT, player_id_int);
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}
	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode ValidateMapFile(const std::string &map_file)
{
	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode ValidateParsedResult(const ParsedResult &parsedResult)
{
	// 检查参数是否合法

	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	error_code = CheckMissingParameters(parsedResult);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}
	// --move
	error_code = ValidateMoveDirection(parsedResult.move_direction);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}

	// --player
	int player_id_int = 0;
	error_code = ValidatePlayerID(parsedResult.player_id);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}

	// --map

	return GameCoreErrorCode::SUCCESS;
}