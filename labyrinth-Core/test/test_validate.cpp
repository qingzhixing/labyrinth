#include <testkit.h>
#include <arg_validate.h>
#include <core_error_code.h>
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

	GameCoreErrorCode error_code = ValidateMoveDirection(move_direction);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidateMoveDirection_Invalid)
{
	std::string move_direction = "invalid";

	GameCoreErrorCode error_code = ValidateMoveDirection(move_direction);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_MOVE_DIRECTION);
}

UnitTest(TestValidatePlayerID_Valid)
{
	std::string player_id = "1";

	GameCoreErrorCode error_code = ValidatePlayerID(player_id);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidatePlayerID_Invalid)
{
	std::string player_id = "invalid";

	GameCoreErrorCode error_code = ValidatePlayerID(player_id);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfGameRange)
{
	std::string player_id = "10";

	GameCoreErrorCode error_code = ValidatePlayerID(player_id);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidatePlayerID_OutOfIntRange)
{
	std::string player_id = "99999999999999999999999999";

	GameCoreErrorCode error_code = ValidatePlayerID(player_id);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::INVALID_PLAYER_ID);
}

UnitTest(TestValidateMapFile_Valid)
{
	std::string map_file = "map_for_test" + std::to_string(rand()) + ".txt";

	// Create a valid map file
	std::ofstream map_file_stream(map_file);
	map_file_stream.close();

	GameCoreErrorCode error_code = ValidateMapFile(map_file);

	// Delete the map file
	std::remove(map_file.c_str());

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestValidateMapFile_Invalid_NotFound)
{
	std::string map_file = "non_existent_" + std::to_string(rand()) + "_map.txt";

	GameCoreErrorCode error_code = ValidateMapFile(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(TestValidateMapFile_Invalid_IsDirectory)
{
	std::string map_file = "test_directory_" + std::to_string(rand());

	// Create a directory
	std::filesystem::create_directory(map_file);

	GameCoreErrorCode error_code = ValidateMapFile(map_file);

	// Remove the directory
	std::filesystem::remove(map_file);

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::MAP_FILE_IS_DIRECTORY);
}