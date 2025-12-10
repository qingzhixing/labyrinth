#include <testkit.h>
#include <argparse.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <debug_log.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

static ParsedResultWithErrorCode CallParseArguments(vector<string> args)
{
	int argc = args.size();
	char *argv[argc];
	for (int i = 0; i < argc; i++)
	{
		DebugLog(LogLevel::DEBUG, "Copying argv[%d] = %s", i, args[i].c_str());
		argv[i] = strdup(args[i].c_str());
	}
	return ParseArguments(argc, argv);
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

UnitTest(TestPlayerID_Long_Invalid)
{
	for (int i = -1; i <= 10; i++)
	{
		auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "--player", std::to_string(i)});

		DebugLog(LogLevel::DEBUG, error_code.toMessage());

		assert(error_code == GameCoreErrorCode::SUCCESS);
		assert(parsed_result.player_id == std::to_string(i));
	}
}

UnitTest(TestPlayerID_Short_Invalid)
{
	for (int i = -1; i <= 10; i++)
	{
		auto [parsed_result, error_code] = CallParseArguments({"labyrinth", "-p", std::to_string(i)});

		DebugLog(LogLevel::DEBUG, error_code.toMessage());

		assert(error_code == GameCoreErrorCode::SUCCESS);
		assert(parsed_result.player_id == std::to_string(i));
	}
}