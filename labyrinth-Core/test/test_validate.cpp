#include <testkit.h>
#include <argument_validator.h>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <fstream>
#include <filesystem>

UnitTest(TestCheckMissingParameters_AllPresent)
{
	ParsedResult parsed_result;
	parsed_result.map_file = "map.txt";
	parsed_result.move_direction = "up";

	GameCoreErrorCode error_code = CheckMissingParameters(parsed_result);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestCheckMissingParameters_MissingSome)
{
	ParsedResult parsed_result;
	parsed_result.map_file = "map.txt";
	parsed_result.move_direction = "";

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