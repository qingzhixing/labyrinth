#include <argument_parser.h>
#include <core_info.h>
#include <debug_log.h>
#include <getopt.h>
#include <string>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>

using std::string;

void ArgumentParser::ResetGetoptState()
{
	// 重置 optind 到 1，确保 getopt_long 从 argv[1] 开始解析
	optind = 1;
}

void ArgumentParser::HandleMapOption(ParsedResult &result, const char *optarg)
{
	DebugLog(LogLevel::DEBUG, "map file: %s", optarg);
	result.map_file = optarg;
}

bool ArgumentParser::HandleVersionOption(int argc, char *argv[], GameCoreErrorCode &error_code)
{
	DebugLog(LogLevel::DEBUG, "version flag");

	// 判断是否有其他参数
	if (optind < argc)
	{
		DebugLog(LogLevel::ERROR, "excessive parameters when --version: %s", argv[optind]);
		error_code = GameCoreErrorCode::EXCESSIVE_PARAMETERS;
		return true;
	}
	else
	{
		PrintVersion();
		error_code = GameCoreErrorCode::SUCCESS;
		return true;
	}
}

void ArgumentParser::HandleMoveOption(ParsedResult &result, int long_index, const char *optarg)
{
	if (long_index == 1) // --move
	{
		result.move_direction = optarg;
	}
}

bool ArgumentParser::HandleHelpOption(GameCoreErrorCode &error_code)
{
	PrintUsage();
	error_code = GameCoreErrorCode::HELP_REQUESTED;
	return true;
}

bool ArgumentParser::HandleInvalidOption(int optopt, GameCoreErrorCode &error_code)
{
	if (optopt == 'm' || optopt == 'p')
	{
		error_code = GameCoreErrorCode::MISSING_PARAMETERS;
	}
	else
	{
		error_code = GameCoreErrorCode::INVALID_PARAMETERS;
	}
	return true;
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
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:vh", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			HandleMapOption(result, optarg);
			break;
		case 'v': // --version
			if (HandleVersionOption(argc, argv, error_code))
			{
				return std::make_pair(result, error_code);
			}
			break;
		case 0:
			HandleMoveOption(result, long_index, optarg);
			break;
		case 'h': // --help
			if (HandleHelpOption(error_code))
			{
				return std::make_pair(result, error_code);
			}
			break;
		case '?': // other invalid options
			if (HandleInvalidOption(optopt, error_code))
			{
				return std::make_pair(result, error_code);
			}
			break;
		default:
			error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			return std::make_pair(result, error_code);
		}
	}

	// 检查参数是否合法
	error_code = GameCoreErrorCode::SUCCESS;
	return std::make_pair(result, error_code);
}

void ArgumentParser::PrintVersion()
{
	std::cout << GAME_NAME_ASCII_ART << std::endl;
	std::cout << GAME_NAME << " " << GAME_VERSION << std::endl;
	std::cout << GAME_DESCRIPTION << std::endl;
	std::cout << "Author: " << AUTHOR << " (" << AUTHOR_EMAIL << ")" << std::endl;
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
	std::cout << "  1. '--move' '-m' must be used together" << std::endl;
}