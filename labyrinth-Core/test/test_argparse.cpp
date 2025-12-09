#include <testkit.h>
#include <argparse.h>
#include <string>
#include <vector>
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
	assert(result.error_code == GameCoreErrorCode::SUCCESS);
}

UnitTest(TestParseVersion_Invalid)
{
	auto result = CallParseArguments({"labyrinth", "--version", "-m", "map.txt"});
	assert(result.error_code == GameCoreErrorCode::EXCESSIVE_PARAMETERS);
}

UnitTest(TestParseMove)
{
	vector<string> directions = {"up", "down", "left", "right"};
	for (auto &direction : directions)
	{
		auto result = CallParseArguments({"labyrinth", "--move", direction});
		assert(result.error_code == GameCoreErrorCode::MISSING_PARAMETERS);
		assert(result.move_direction == direction);
	}
}

UnitTest(TestParseHelp)
{
	auto result = CallParseArguments({"labyrinth", "--help"});
	assert(result.error_code == GameCoreErrorCode::HELP_REQUESTED);
}