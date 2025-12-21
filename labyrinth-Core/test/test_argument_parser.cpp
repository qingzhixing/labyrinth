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

	static ParsedResult TestHandleMapOption(ArgumentParser &parser, const ParsedResult &result, const char *optarg)
	{
		return parser.HandleMapOption(result, optarg);
	}

	static ErrorCode TestHandleVersionOption(ArgumentParser &parser, int argc, char *argv[])
	{
		return parser.HandleVersionOption(argc, argv);
	}

	static ParsedResult TestHandleMoveOption(ArgumentParser &parser, const ParsedResult &result, const char *optarg)
	{
		return parser.HandleMoveOption(result, optarg);
	}

	static ErrorCode TestHandleHelpOption(ArgumentParser &parser)
	{
		return parser.HandleHelpOption();
	}

	static ParsedResult TestHandleValidateOption(ArgumentParser &parser, const ParsedResult &result)
	{
		return parser.HandleValidateOption(result);
	}

	static ErrorCode TestHandleInvalidOption(ArgumentParser &parser, int optopt)
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

UnitTest(ArgumentParser_HandleValidateOption)
{
	ArgumentParser parser;
	ParsedResult initial_result;
	ParsedResult result = ArgumentParserTest::TestHandleValidateOption(parser, initial_result);
	assert(result.validate == true);
}

// 测试HandleMapOption函数
UnitTest(ArgumentParser_HandleMapOption)
{
	ArgumentParser parser;
	ParsedResult initial_result;

	// 测试正常情况
	ParsedResult result1 = ArgumentParserTest::TestHandleMapOption(parser, initial_result, "test.map");
	assert(result1.map_file == "test.map");

	// 测试空字符串
	ParsedResult result2 = ArgumentParserTest::TestHandleMapOption(parser, initial_result, "");
	assert(result2.map_file == "");

	// 测试长路径
	ParsedResult result3 = ArgumentParserTest::TestHandleMapOption(parser, initial_result, "/path/to/map/file.map");
	assert(result3.map_file == "/path/to/map/file.map");
}

// 测试HandleMoveOption函数
UnitTest(ArgumentParser_HandleMoveOption)
{
	ArgumentParser parser;
	ParsedResult initial_result;

	// 测试各种方向
	for (auto direction : {"up", "down", "left", "right", "invalid"})
	{
		ParsedResult result = ArgumentParserTest::TestHandleMoveOption(parser, initial_result, direction);
		assert(result.direction == direction);
	}
}

// 测试HandleHelpOption函数
UnitTest(ArgumentParser_HandleHelpOption)
{
	ArgumentParser parser;

	auto error_code = ArgumentParserTest::TestHandleHelpOption(parser);
	assert(error_code == ErrorCode::HELP_REQUESTED);
}

// 测试HandleInvalidOption函数
UnitTest(ArgumentParser_HandleInvalidOption)
{
	ArgumentParser parser;

	// 测试缺失参数的情况
	auto error1 = ArgumentParserTest::TestHandleInvalidOption(parser, 'm');
	assert(error1 == ErrorCode::MISSING_PARAMETERS);

	auto error2 = ArgumentParserTest::TestHandleInvalidOption(parser, 'p');
	assert(error2 == ErrorCode::MISSING_PARAMETERS);

	// 测试无效参数的情况
	auto error3 = ArgumentParserTest::TestHandleInvalidOption(parser, 'x');
	assert(error3 == ErrorCode::INVALID_PARAMETERS);

	auto error4 = ArgumentParserTest::TestHandleInvalidOption(parser, 'z');
	assert(error4 == ErrorCode::INVALID_PARAMETERS);
}

static char **MakeArgv(const std::vector<std::string> &args)
{
	// 分配内存
	char **argv = new char *[args.size() + 1];
	for (size_t i = 0; i < args.size(); ++i)
	{
		argv[i] = strdup(args[i].c_str());
	}
	argv[args.size()] = nullptr;
	return argv;
}

// 测试HandleVersionOption函数 - 无额外参数的情况
UnitTest(ArgumentParser_HandleVersionOption_NoExtraParams)
{
	ArgumentParser parser;

	// 创建测试参数
	std::vector<std::string> args = {"program", "--version"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto error_code = ArgumentParserTest::TestHandleVersionOption(parser, argc, argv);
	assert(error_code == ErrorCode::VERSION_REQUESTED);
}

// 测试HandleVersionOption函数 - 有额外参数的情况
UnitTest(ArgumentParser_HandleVersionOption_WithExtraParams)
{
	ArgumentParser parser;

	// 创建测试参数（有额外参数）
	std::vector<std::string> args = {"program", "--version", "extra"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto error_code = ArgumentParserTest::TestHandleVersionOption(parser, argc, argv);
	assert(error_code == ErrorCode::EXCESSIVE_PARAMETERS);
}

// 测试完整的ParseArguments函数 - 正常情况
UnitTest(ArgumentParser_ParseArguments_Normal)
{
	ArgumentParser parser;

	std::vector<std::string> args = {"program", "-m", "test.map", "--move", "up", "--validate"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == ErrorCode::SUCCESS);
	assert(result.map_file == "test.map");
	assert(result.direction == "up");
	assert(result.validate == true);
}

// 测试完整的ParseArguments函数 - 帮助请求
UnitTest(ArgumentParser_ParseArguments_Help)
{
	ArgumentParser parser;

	std::vector<std::string> args = {"program", "-h"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == ErrorCode::HELP_REQUESTED);
}

// 测试完整的ParseArguments函数 - 版本请求
UnitTest(ArgumentParser_ParseArguments_Version)
{
	ArgumentParser parser;

	std::vector<std::string> args = {"program", "-v"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == ErrorCode::VERSION_REQUESTED);
}

// 测试完整的ParseArguments函数 - 无效选项
UnitTest(ArgumentParser_ParseArguments_InvalidOption)
{
	ArgumentParser parser;

	std::vector<std::string> args = {"program", "-x", "invalid"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == ErrorCode::INVALID_PARAMETERS);
}

// 测试完整的ParseArguments函数 - 缺失参数
UnitTest(ArgumentParser_ParseArguments_MissingParameters)
{
	ArgumentParser parser;

	std::vector<std::string> args = {"program", "-m"};
	char **argv = MakeArgv(args);
	int argc = args.size();

	auto [result, error_code] = parser.ParseArguments(argc, argv);
	assert(error_code == ErrorCode::MISSING_PARAMETERS);
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
	assert(output.find(GAME_NAME) != std::string::npos);
	assert(output.find(GAME_VERSION) != std::string::npos);
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