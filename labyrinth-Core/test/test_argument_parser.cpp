#include <argument_parser.h>
#include <testkit.h>
#include <debug_log.h>
#include <iostream>
#include <sstream>
#include <cstring>

// 测试友元类定义
class ArgumentParserTest
{
public:
	static void TestResetGetoptState(ArgumentParser &parser)
	{
		parser.ResetGetoptState();
		// 重置后optind应该为1
		// 注意：由于optind是全局变量，这个测试可能会影响其他测试
	}

	static void TestHandleMapOption(ArgumentParser &parser, ParsedResult &result, const char *optarg)
	{
		parser.HandleMapOption(result, optarg);
	}

	static bool TestHandleVersionOption(ArgumentParser &parser, int argc, char *argv[], GameCoreErrorCode &error_code)
	{
		return parser.HandleVersionOption(argc, argv, error_code);
	}

	static void TestHandleMoveOption(ArgumentParser &parser, ParsedResult &result, const char *optarg)
	{
		parser.HandleMoveOption(result, optarg);
	}

	static bool TestHandleHelpOption(ArgumentParser &parser, GameCoreErrorCode &error_code)
	{
		return parser.HandleHelpOption(error_code);
	}

	static GameCoreErrorCode TestHandleInvalidOption(ArgumentParser &parser, int optopt)
	{
		return parser.HandleInvalidOption(optopt);
	}
};

// 测试ResetGetoptState函数
UnitTest(ArgumentParser_ResetGetoptState)
{
	ArgumentParser parser;
	ArgumentParserTest::TestResetGetoptState(parser);
	// 这个函数主要重置全局状态，难以直接验证
	// 但调用它确保没有崩溃或异常
}

// 测试HandleMapOption函数
UnitTest(ArgumentParser_HandleMapOption)
{
	ArgumentParser parser;
	ParsedResult result;

	// 测试正常情况
	ArgumentParserTest::TestHandleMapOption(parser, result, "test.map");
	assert(result.map_file == "test.map");

	// 测试空字符串
	ArgumentParserTest::TestHandleMapOption(parser, result, "");
	assert(result.map_file == "");

	// 测试长路径
	ArgumentParserTest::TestHandleMapOption(parser, result, "/path/to/map/file.map");
	assert(result.map_file == "/path/to/map/file.map");
}

// 测试HandleMoveOption函数
UnitTest(ArgumentParser_HandleMoveOption)
{
	ArgumentParser parser;
	ParsedResult result;

	// 测试各种方向
	for (auto direction : {"up", "down", "left", "right", "invalid"})
	{
		ArgumentParserTest::TestHandleMoveOption(parser, result, direction);
		assert(result.move_direction == direction);
	}
}

// 测试HandleHelpOption函数
UnitTest(ArgumentParser_HandleHelpOption)
{
	ArgumentParser parser;
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	bool should_stop = ArgumentParserTest::TestHandleHelpOption(parser, error_code);
	assert(should_stop == true);
	assert(error_code == GameCoreErrorCode::HELP_REQUESTED);
}

// 测试HandleInvalidOption函数
UnitTest(ArgumentParser_HandleInvalidOption)
{
	ArgumentParser parser;

	// 测试缺失参数的情况
	GameCoreErrorCode error1 = ArgumentParserTest::TestHandleInvalidOption(parser, 'm');
	assert(error1 == GameCoreErrorCode::MISSING_PARAMETERS);

	GameCoreErrorCode error2 = ArgumentParserTest::TestHandleInvalidOption(parser, 'p');
	assert(error2 == GameCoreErrorCode::MISSING_PARAMETERS);

	// 测试无效参数的情况
	GameCoreErrorCode error3 = ArgumentParserTest::TestHandleInvalidOption(parser, 'x');
	assert(error3 == GameCoreErrorCode::INVALID_PARAMETERS);

	GameCoreErrorCode error4 = ArgumentParserTest::TestHandleInvalidOption(parser, 'z');
	assert(error4 == GameCoreErrorCode::INVALID_PARAMETERS);
}

// 测试HandleVersionOption函数 - 无额外参数的情况
UnitTest(ArgumentParser_HandleVersionOption_NoExtraParams)
{
	ArgumentParser parser;
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 创建测试参数
	char *argv[] = {"program", "--version", nullptr};
	int argc = 2;

	bool should_stop = ArgumentParserTest::TestHandleVersionOption(parser, argc, argv, error_code);
	assert(should_stop == true);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

// 测试HandleVersionOption函数 - 有额外参数的情况
UnitTest(ArgumentParser_HandleVersionOption_WithExtraParams)
{
	ArgumentParser parser;
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 创建测试参数（有额外参数）
	char *argv[] = {"program", "--version", "extra", nullptr};
	int argc = 3;

	bool should_stop = ArgumentParserTest::TestHandleVersionOption(parser, argc, argv, error_code);
	assert(should_stop == true);
	assert(error_code == GameCoreErrorCode::EXCESSIVE_PARAMETERS);
}

// 测试完整的ParseArguments函数 - 正常情况
UnitTest(ArgumentParser_ParseArguments_Normal)
{
	ArgumentParser parser;

	char *argv[] = {"program", "-m", "test.map", "--move", "up", nullptr};
	int argc = 5;

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == GameCoreErrorCode::SUCCESS);
	assert(result.map_file == "test.map");
	assert(result.move_direction == "up");
}

// 测试完整的ParseArguments函数 - 帮助请求
UnitTest(ArgumentParser_ParseArguments_Help)
{
	ArgumentParser parser;

	char *argv[] = {"program", "-h", nullptr};
	int argc = 2;

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == GameCoreErrorCode::HELP_REQUESTED);
}

// 测试完整的ParseArguments函数 - 版本请求
UnitTest(ArgumentParser_ParseArguments_Version)
{
	ArgumentParser parser;

	char *argv[] = {"program", "-v", nullptr};
	int argc = 2;

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == GameCoreErrorCode::SUCCESS);
}

// 测试完整的ParseArguments函数 - 无效选项
UnitTest(ArgumentParser_ParseArguments_InvalidOption)
{
	ArgumentParser parser;

	char *argv[] = {"program", "-x", "invalid", nullptr};
	int argc = 3;

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == GameCoreErrorCode::INVALID_PARAMETERS);
}

// 测试完整的ParseArguments函数 - 缺失参数
UnitTest(ArgumentParser_ParseArguments_MissingParameters)
{
	ArgumentParser parser;

	char *argv[] = {"program", "-m", nullptr};
	int argc = 2;

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == GameCoreErrorCode::MISSING_PARAMETERS);
}

// 测试静态函数PrintVersion
UnitTest(ArgumentParser_PrintVersion)
{
	// 重定向stdout来捕获输出
	std::stringstream buffer;
	std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

	ArgumentParser::PrintVersion();

	std::cout.rdbuf(old); // 恢复stdout
	std::string output = buffer.str();

	// 检查输出是否包含预期的内容
	assert(output.find("Labyrinth Game") != std::string::npos);
	assert(output.find("v0.1.0") != std::string::npos);
}

// 测试静态函数PrintUsage
UnitTest(ArgumentParser_PrintUsage)
{
	// 重定向stdout来捕获输出
	std::stringstream buffer;
	std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

	ArgumentParser::PrintUsage();

	std::cout.rdbuf(old); // 恢复stdout
	std::string output = buffer.str();

	// 检查输出是否包含预期的内容
	assert(output.find("Usage:") != std::string::npos);
	assert(output.find("-m, --map") != std::string::npos);
	assert(output.find("--move DIRECTION") != std::string::npos);
}