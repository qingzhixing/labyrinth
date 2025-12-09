#include <argparse.h>
#include <iostream>
#include <getopt.h>
#include <string>
#include <core_info.h>
#include <core_error_code.h>
#include <debug_log.h>
#include <vector>
#include <memory>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

void PrintVersion()
{
	cout << GAME_NAME_ASCII_ART << endl;
	cout << GAME_NAME << " " << GAME_VERSION << endl;
	cout << GAME_DESCRIPTION << endl;
	cout << "Author: " << AUTHOR << " (" << AUTHOR_EMAIL << ")" << endl;
}

void PrintUsage()
{
	cout << "Usage: "
		 << PROGRAM_NAME
		 << " [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [-v|--version]"
		 << endl;

	cout << "Options:" << endl;
	cout << "  -m, --map FILE    Specify the map file to use" << endl;

	cout << "  -p, --player ID    Specify the player ID to use" << endl;

	cout << "      --move DIRECTION (up, down, left, right)    Specify the direction to move" << endl;

	cout << "  -v, --version    Show the version information" << endl;

	cout << "  -h, --help    Show this help message" << endl;

	cout << "Tips:" << endl
		 << "  1. '-p' '-m' can exchange their positions" << endl
		 << "  2. '--move' must be used with '-p'" << endl;
}

ParsedResult ParseArguments(int argc, char *argv[])
{
	// 重置 optind 到 1，确保 getopt_long 从 argv[1] 开始解析
	optind = 1;

	DebugLog(LogLevel::INFO, "Start parsing arguments");
	DebugLog(LogLevel::DEBUG, "argc: %d", argc);
	for (int i = 0; i < argc; i++)
	{
		DebugLog(LogLevel::DEBUG, "argv[%d]: %s", i, argv[i]);
	}

	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"player", required_argument, nullptr, 'p'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 'v'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	ParsedResult result{};
	string player_id_str{};

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			DebugLog(LogLevel::DEBUG, "map file: %s", optarg);
			result.map_file = optarg;
			break;
		case 'p':
			DebugLog(LogLevel::DEBUG, "player ID: %s", optarg);
			player_id_str = optarg;
			break;
		case 'v': // --version
			DebugLog(LogLevel::DEBUG, "version flag");

			// 判断是否有其他参数
			if (optind < argc)
			{
				DebugLog(LogLevel::ERROR, "excessive parameters when --version: %s", argv[optind]);
				result.error_code = GameCoreErrorCode::EXCESSIVE_PARAMETERS;
			}
			else
			{
				DebugLog(LogLevel::INFO, "Display Version Information");
				PrintVersion();
				result.error_code = GameCoreErrorCode::SUCCESS;
			}
			return result;
			break;
		case 0:
			if (long_index == 2) // --move
			{
				DebugLog(LogLevel::DEBUG, "move direction: %s", optarg);
				result.move_direction = optarg;
			}
			break;
		case 'h': // --help
			DebugLog(LogLevel::DEBUG, "Display help message");
			PrintUsage();
			result.error_code = GameCoreErrorCode::HELP_REQUESTED;
			return result;

			break;
		case '?': // other invalid options
			if (optopt == 'm' || optopt == 'p')
			{
				DebugLog(LogLevel::ERROR, "missing parameter: %c", optopt);
				result.error_code = GameCoreErrorCode::MISSING_PARAMETERS;
				return result;
			}
			else
			{
				DebugLog(LogLevel::ERROR, "invalid parameter: [%d]%c", optopt, optopt);
				result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
				return result;
			}

			break;
		default:
			DebugLog(LogLevel::ERROR, "unknown parameter:[%d]%c", opt, opt);
			PrintUsage();
			result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			return result;

			break;
		}
	}
	// 检查参数是否合法

	// Check Missing Parameters
	bool missing_parameters = false;
	if (result.map_file.empty())
	{
		DebugLog(LogLevel::ERROR, "missing map file");
		missing_parameters = true;
	}
	if (player_id_str.empty())
	{
		DebugLog(LogLevel::ERROR, "missing player ID");
		missing_parameters = true;
	}
	if (result.move_direction.empty())
	{
		DebugLog(LogLevel::ERROR, "missing move direction");
		missing_parameters = true;
	}
	if (missing_parameters)
	{
		PrintUsage();
		result.error_code = GameCoreErrorCode::MISSING_PARAMETERS;
		return result;
	}

	// --move
	if (result.move_direction != "up" && result.move_direction != "down" && result.move_direction != "left" && result.move_direction != "right")
	{
		DebugLog(LogLevel::ERROR, "invalid move direction: %s", result.move_direction.c_str());
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
		return result;
	}

	// --player
	try
	{
		DebugLog(LogLevel::INFO, "Transforming player ID: %s", player_id_str.c_str());
		result.player_id = std::stoi(player_id_str);
	}
	catch (const std::invalid_argument &e)
	{
		DebugLog(LogLevel::ERROR, "player ID is not a number: %s", player_id_str.c_str());
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
		return result;
	}
	catch (const std::out_of_range &e)
	{
		DebugLog(LogLevel::ERROR, "player ID out of range: %s", player_id_str.c_str());
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
		return result;
	}

	return std::move(result);
}