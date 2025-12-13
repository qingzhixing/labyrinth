#include <testkit.h>
#include <argument_parser.h>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <string>
#include <vector>
#include <cstring>
#include <debug_log.h>

using std::string;
using std::vector;

static ParsedResultWithErrorCode CallParseArguments(vector<string> args)
{
	int argc = args.size();
	char *argv[argc];
	for (int i = 0; i < argc; i++)
	{
		argv[i] = strdup(args[i].c_str());
	}

	// Create argument parser instance
	ArgumentParser parser;
	return parser.ParseArguments(argc, argv);
}

UnitTest(TestParseVersion_Long_Valid)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "--version"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseVersion_Long_Invalid)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "--version", "-m", "map.txt"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::EXCESSIVE_PARAMETERS);
}

UnitTest(TestParseVersion_Short_Valid)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "-v"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseVersion_Short_Invalid)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "-v", "-p", "1"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::EXCESSIVE_PARAMETERS);
}

UnitTest(TestParseMove)
{
	vector<string> directions = {"up", "down", "left", "right"};
	for (auto &direction : directions)
	{
		auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "--move", direction});

		DebugLog(LogLevel::DEBUG, error_code.toMessage());

		assert(error_code == GameCoreErrorCode::SUCCESS);
		assert(parsed_result.move_direction == direction);
	}
}

UnitTest(TestParseHelp_Long)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "--help"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::HELP_REQUESTED);
}

UnitTest(TestParseHelp_Short)
{
	auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "-h"});

	DebugLog(LogLevel::DEBUG, error_code.toMessage());

	assert(error_code == GameCoreErrorCode::HELP_REQUESTED);
}