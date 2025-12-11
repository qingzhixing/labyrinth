#include <testkit.h>
#include <arg_validate.h>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <fstream>
#include <filesystem>

UnitTest(TestCheckMissingParameters_AllPresent)
{
	ParsedResult parsed_result;
	parsed_result.map_file = "map.txt";
	parsed_result.move_direction = "up";
	parsed_result.player_id = "1";

	GameCoreErrorCode error_code = CheckMissingParameters(parsed_result);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestCheckMissingParameters_MissingSome)
{
	ParsedResult parsed_result;
	parsed_result.map_file = "map.txt";
	parsed_result.move_direction = "";
	parsed_result.player_id = "";

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
	std::string player_id_str = "0";

	auto [player_id_int, error_code] = ValidatePlayerID(player_id_str);
	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(player_id_int == 0);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidatePlayerID_Invalid_Empty)
{
	std::string player_id_str = "";

	auto [player_id_int, error_code] = ValidatePlayerID(player_id_str);
	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(player_id_int == NO_PLAYER_ID);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidatePlayerID_Invalid)
{
	std::string player_id_str = "invalid";

	auto [player_id_int, error_code] = ValidatePlayerID(player_id_str);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfGameRange)
{
	std::string player_id_str = "10";

	auto [player_id_int, error_code] = ValidatePlayerID(player_id_str);
	DebugLog(LogLevel::DEBUG, error_code.toMessage());
	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfIntRange)
{
	std::string player_id_str = "99999999999999999999999999";

	auto [player_id_int, error_code] = ValidatePlayerID(player_id_str);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}