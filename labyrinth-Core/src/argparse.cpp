#include <argparse.h>
#include <iostream>
#include <getopt.h>
#include <string>
#include <core_info.h>
#include <core_error_code.h>
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
	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"player", required_argument, nullptr, 'p'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 'v'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	ParsedResult result;
	string player_id_str;

	bool version_flag = false;

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			result.map_file = optarg;
			break;
		case 'p':
			player_id_str = optarg;
			break;
		case 0:
			if (long_index == 2)
			{
				result.move_direction = optarg;
			}
			else if (long_index == 3)
			{
				version_flag = true;
			}
			break;
		case 'h':
			PrintUsage();
			result.error_code = GameCoreErrorCode::HELP_REQUESTED;
		case '?':
			if (optopt == 'm' || optopt == 'p')
			{
				result.error_code = GameCoreErrorCode::MISSING_PARAMETERS;
			}
			else
			{
				result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			}
		default:
			PrintUsage();
			result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
		}
	}

	// 检查必需参数是否提供
	if (result.map_file.empty() || player_id_str.empty() || result.move_direction.empty())
	{
		result.error_code = GameCoreErrorCode::MISSING_PARAMETERS;
	}

	// 检查参数是否合法

	// --version
	if (version_flag)
	{
		// 判断是否有其他参数
		if (optind < argc)
		{
			result.error_code = GameCoreErrorCode::EXCESSIVE_PARAMETERS;
		}
		PrintVersion();
		result.error_code = GameCoreErrorCode::SUCCESS;
	}

	// --move
	if (result.move_direction != "up" && result.move_direction != "down" && result.move_direction != "left" && result.move_direction != "right")
	{
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
	}

	// --player
	try
	{
		result.player_id = std::stoi(player_id_str);
	}
	catch (const std::invalid_argument &e)
	{
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
	}
	catch (const std::out_of_range &e)
	{
		result.error_code = GameCoreErrorCode::INVALID_PARAMETERS;
	}

	return std::move(result);
}