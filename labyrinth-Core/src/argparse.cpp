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
#include <core_info.h>

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
		 << "  2. '-p' '--move' '-m' must be used together" << endl;
}

ParsedResultWithErrorCode ParseArguments(int argc, char *argv[])
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
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:vh", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			DebugLog(LogLevel::DEBUG, "map file: %s", optarg);
			result.map_file = optarg;
			break;
		case 'p':
			DebugLog(LogLevel::DEBUG, "player ID: %s", optarg);
			result.player_id = optarg;
			break;
		case 'v': // --version
			DebugLog(LogLevel::DEBUG, "version flag");

			// 判断是否有其他参数
			if (optind < argc)
			{
				DebugLog(LogLevel::ERROR, "excessive parameters when --version: %s", argv[optind]);
				error_code = GameCoreErrorCode::EXCESSIVE_PARAMETERS;
			}
			else
			{
				DebugLog(LogLevel::INFO, "Display Version Information");
				PrintVersion();
				error_code = GameCoreErrorCode::SUCCESS;
			}
			return std::make_pair(result, error_code);
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
			error_code = GameCoreErrorCode::HELP_REQUESTED;
			return std::make_pair(result, error_code);

			break;
		case '?': // other invalid options
			if (optopt == 'm' || optopt == 'p')
			{
				DebugLog(LogLevel::ERROR, "missing parameter: %c", optopt);
				error_code = GameCoreErrorCode::MISSING_PARAMETERS;
			}
			else
			{
				DebugLog(LogLevel::ERROR, "invalid parameter: [%d]%c", optopt, optopt);
				error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			}
			return std::make_pair(result, error_code);
			break;
		default:
			DebugLog(LogLevel::ERROR, "unknown parameter:[%d]%c", opt, opt);
			error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			return std::make_pair(result, error_code);

			break;
		}
	}

	// 检查参数是否合法
	error_code = GameCoreErrorCode::SUCCESS;
	return std::make_pair(result, error_code);
}

static GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsedResult)
{
	bool missing_parameters = false;
	if (parsedResult.map_file.empty())
	{
		DebugLog(LogLevel::ERROR, "missing map file");
		missing_parameters = true;
	}
	if (parsedResult.move_direction.empty())
	{
		DebugLog(LogLevel::ERROR, "missing move direction");
		missing_parameters = true;
	}
	if (missing_parameters)
	{
		return GameCoreErrorCode::MISSING_PARAMETERS;
	}
	return GameCoreErrorCode::SUCCESS;
}

static GameCoreErrorCode ValidateMoveDirection(const std::string &move_direction)
{
	if (move_direction != "up" && move_direction != "down" && move_direction != "left" && move_direction != "right")
	{
		DebugLog(LogLevel::ERROR, "invalid move direction: %s", move_direction.c_str());
		return GameCoreErrorCode::INVALID_MOVE_DIRECTION;
	}
	return GameCoreErrorCode::SUCCESS;
}

static GameCoreErrorCode ValidatePlayerID(const std::string &player_id)
{
	int player_id_int = -1;
	try
	{
		player_id_int = std::stoi(player_id);
	}
	catch (const std::invalid_argument &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be a number: %s", player_id.c_str());
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}
	catch (const std::out_of_range &e)
	{
		DebugLog(LogLevel::ERROR, "Player ID out of int range: %s", player_id.c_str());
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}

	if (player_id_int < 0 || player_id_int > MAX_PLAYER_COUNT)
	{
		DebugLog(LogLevel::ERROR, "Player ID must be greater than 0 and less than %d: %d", MAX_PLAYER_COUNT, player_id_int);
		return GameCoreErrorCode::INVALID_PLAYER_ID;
	}
	return GameCoreErrorCode::SUCCESS;
}

static GameCoreErrorCode ValidateMapFile(const std::string &map_file)
{
	return GameCoreErrorCode::SUCCESS;
}

GameCoreErrorCode ValidateParsedResult(const ParsedResult &parsedResult)
{
	// 检查参数是否合法

	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	error_code = CheckMissingParameters(parsedResult);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}
	// --move
	error_code = ValidateMoveDirection(parsedResult.move_direction);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}

	// --player
	int player_id_int = 0;
	error_code = ValidatePlayerID(parsedResult.player_id);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		return error_code;
	}

	// --map

	return GameCoreErrorCode::SUCCESS;
}