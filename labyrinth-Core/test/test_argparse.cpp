#include <testkit.h>
#include <argparse.h>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

static ParsedResult CallParseArguments(vector<string> args)
{
	int argc = args.size();
	char *argv[argc];
	for (int i = 0; i < argc; i++)
	{
		argv[i] = const_cast<char *>(args[i].c_str());
	}
	return ParseArguments(argc, argv);
}

UnitTest(TestParseVersion_Valid)
{
	auto result = CallParseArguments({"labyrinth", "--version"});
	PrintGameCoreErrorMessage(result.error_code);
	assert(result.error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseVersion_Invalid)
{
	auto result = CallParseArguments({"labyrinth", "--version", "-m", "map.txt"});
	PrintGameCoreErrorMessage(result.error_code);
	assert(result.error_code == GameCoreErrorCode::EXCESSIVE_PARAMETERS);
}

UnitTest(TestParseMove)
{
	vector<string> directions = {"up", "down", "left", "right"};
	for (auto &direction : directions)
	{
		auto result = CallParseArguments({"labyrinth", "--move", direction});
		PrintGameCoreErrorMessage(result.error_code);
		assert(result.error_code == GameCoreErrorCode::MISSING_PARAMETERS);
		cout << "result.move_direction: " << result.move_direction << endl;
		assert(result.move_direction == direction);
	}
}

UnitTest(TestParseHelp)
{
	auto result = CallParseArguments({"labyrinth", "--help"});
	PrintGameCoreErrorMessage(result.error_code);
	assert(result.error_code == GameCoreErrorCode::HELP_REQUESTED);
}