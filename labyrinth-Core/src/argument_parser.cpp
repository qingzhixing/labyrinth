#include <argument_parser.h>
#include <core_info.h>
#include <debug_log.h>
#include <getopt.h>
#include <string>
#include <types/error_code.h>
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>
#include <format>

using std::string;

void ArgumentParser::ResetGetoptState()
{
	// 重置 optind 到 1，确保 getopt_long 从 argv[1] 开始解析
	optind = 1;
}

ParsedResult ArgumentParser::HandleMapOption(
	const ParsedResult &result,
	const char *optarg)
{
	DebugLog(LogLevel::DEBUG, "map file: %s", optarg);

	ParsedResult updated_result = result;
	updated_result.map_file = optarg;
	return updated_result;
}

ErrorCode ArgumentParser::HandleVersionOption(
	int argc,
	char *argv[])
{

	DebugLog(LogLevel::DEBUG, "version optind: %d", optind);

	// 判断是否有其他参数
	if (optind + 1 < argc)
	{
		DebugLog(
			LogLevel::ERROR,
			"excessive parameters when --version: %s",
			argv[optind]);
		return ErrorCode::EXCESSIVE_PARAMETERS;
	}
	else
	{
		PrintVersion();
		return ErrorCode::VERSION_REQUESTED;
	}
}

ParsedResult ArgumentParser::HandleMoveOption(
	const ParsedResult &result,
	const char *optarg)
{
	ParsedResult updated_result = result;
	updated_result.direction = optarg;
	return updated_result;
}

ErrorCode ArgumentParser::HandleHelpOption()
{
	PrintUsage();
	return ErrorCode::HELP_REQUESTED;
}

ErrorCode ArgumentParser::HandleInvalidOption(int optopt)
{
	ErrorCode error_code = ErrorCode::INVALID_PARAMETERS;

	if (optopt == 'm' || optopt == 'p')
	{
		error_code = ErrorCode::MISSING_PARAMETERS;
	}

	return error_code;
}

ParsedResultWithErrorCode ArgumentParser::ParseArguments(int argc, char *argv[])
{
	ResetGetoptState();

	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 'v'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	ParsedResult result{};

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(
				argc,
				argv,
				"m:vh",
				long_options,
				&long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			result = HandleMapOption(result, optarg);
			break;
		case 'v': // --version
			return {
				.parsed_result = result,
				.error_code = HandleVersionOption(argc, argv)};
		case 0: // --move
			result = HandleMoveOption(result, optarg);
			break;
		case 'h': // --help
			return {
				.parsed_result = result,
				.error_code = HandleHelpOption()};
		case '?': // other invalid options
			return {
				.parsed_result = result,
				.error_code = HandleInvalidOption(optopt)};
		default:
			return {
				.parsed_result = result,
				.error_code = ErrorCode::INVALID_PARAMETERS};
		}
	}

	// 检查参数是否合法
	return {
		.parsed_result = result,
		.error_code = ErrorCode::SUCCESS};
}

void ArgumentParser::PrintVersion()
{
	std::cout << GAME_NAME_ASCII_ART << std::endl;
	std::cout << std::format("{} ({})", GAME_NAME, GAME_VERSION) << std::endl;
	std::cout << CORE_DESCRIPTION << std::endl;
	std::cout << std::format("Author: {} <{}>", AUTHOR, AUTHOR_EMAIL) << std::endl;
}

void ArgumentParser::PrintUsage()
{
	std::cout
		<< "Usage: "
		<< PROGRAM_NAME
		<< " [-m|--map FILE] [--move DIRECTION] [-v|--version]"
		<< std::endl;

	std::cout << "Options:" << std::endl;
	std::cout
		<< "  -m, --map FILE    Specify the map file to use"
		<< std::endl;

	std::cout
		<< "      --move DIRECTION (up, down, left, right)    "
		<< "Specify the direction to move"
		<< std::endl;

	std::cout
		<< "  -v, --version    Show the version information"
		<< std::endl;

	std::cout
		<< "  -h, --help    Show this help message"
		<< std::endl;

	std::cout << "Tips:" << std::endl;
	std::cout
		<< "  '--move' '-m' must be used together"
		<< std::endl;
}