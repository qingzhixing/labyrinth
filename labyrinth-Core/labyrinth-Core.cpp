#include <iostream>
#include <testkit.h>
#include <getopt.h>
#include <string>
#include <core_info.h>
#include <core_error_code.h>

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Print the version information of the program.
 *
 */
void PrintVersion()
{
	cout << GAME_NAME_ASCII_ART << endl;
	cout << GAME_NAME << " " << GAME_VERSION << endl;
	cout << GAME_DESCRIPTION << endl;
	cout << "Author: " << AUTHOR << " (" << AUTHOR_EMAIL << ")" << endl;
}

/**
 * @brief Print the usage message of the program.
 *
 * labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [-v|--version]
 */
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

GameCoreErrorCode ParseArguments(int argc, char *argv[])
{
	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"player", required_argument, nullptr, 'p'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 'v'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	string map_file;
	string player_id;
	string move_direction;

	bool version_flag = false;

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			map_file = optarg;
			break;
		case 'p':
			player_id = optarg;
			break;
		case 0:
			if (long_index == 2)
			{
				move_direction = optarg;
			}
			else if (long_index == 3)
			{
				version_flag = true;
			}
			break;
		case 'h':
			PrintUsage();
			exit(GameCoreErrorCode::SUCCESS);
		case '?':
			if (optopt == 'm' || optopt == 'p')
			{
				exit(GameCoreErrorCode::MISSING_PARAMETERS);
			}
			else
			{
				exit(GameCoreErrorCode::INVALID_PARAMETERS);
			}
		default:
			PrintUsage();
			exit(GameCoreErrorCode::INVALID_PARAMETERS);
		}
	}

	// 检查必需参数是否提供
	if (map_file.empty() || player_id.empty() || move_direction.empty())
	{
		exit(GameCoreErrorCode::MISSING_PARAMETERS);
	}

	// 检查参数是否合法

	// --version
	if (version_flag)
	{
		// 判断是否有其他参数
		if (optind < argc)
		{
			exit(GameCoreErrorCode::EXCESSIVE_PARAMETERS);
		}
		PrintVersion();
		exit(GameCoreErrorCode::SUCCESS);
	}

	if (move_direction != "up" && move_direction != "down" && move_direction != "left" && move_direction != "right")
	{
		exit(GameCoreErrorCode::INVALID_PARAMETERS);
	}

	return GameCoreErrorCode::SUCCESS;
}

int main(int argc, char *argv[])
{
}

UnitTest(TestPrintVersion)
{
	PrintVersion();
}

UnitTest(TestPrintUsage)
{
	PrintUsage();
}