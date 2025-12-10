#include <testkit.h>
#include <arg_validate.h>
#include <core_error_code.h>
#include <debug_log.h>
#include <fstream>
#include <filesystem>

UnitTest(TestCheckMissingParameters_AllPresent)
{
	ParsedResult parsed_result;
	parsed_result.mapFile = "map.txt";
	parsed_result.move_direction = "up";
	parsed_result.playerID = "1";

	GameCoreErrorCode error_code = CheckMissingParameters(parsed_result);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestCheckMissingParameters_MissingSome)
{
	ParsedResult parsed_result;
	parsed_result.mapFile = "map.txt";
	parsed_result.move_direction = "";
	parsed_result.playerID = "";

	GameCoreErrorCode error_code = CheckMissingParameters(parsed_result);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MISSING_PARAMETERS);
}

UnitTest(TestValidateMoveDirection_Valid)
{
	std::string move_direction = "up";

	auto [direction, error_code] = ValidateMoveDirection(move_direction);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(direction == Direction::UP);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidateMoveDirection_Invalid)
{
	std::string move_direction = "invalid";

	auto [direction, error_code] = ValidateMoveDirection(move_direction);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(direction == Direction::INVALID);
	assert(error_code == GameCoreErrorCode::INVALID_MOVE_DIRECTION);
}

UnitTest(TestValidatePlayerID_Valid)
{
	std::string playerID = "1";

	auto [player_id_int, error_code] = ValidatePlayerID(playerID);
	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(player_id_int == 1);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidatePlayerID_Invalid)
{
	std::string playerID = "invalid";

	auto [player_id_int, error_code] = ValidatePlayerID(playerID);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfGameRange)
{
	std::string playerID = "10";

	auto [player_id_int, error_code] = ValidatePlayerID(playerID);
	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfIntRange)
{
	std::string playerID = "99999999999999999999999999";

	auto [player_id_int, error_code] = ValidatePlayerID(playerID);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}