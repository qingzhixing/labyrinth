#include <iostream>
#include <testkit.h>
#include <getopt.h>
#include <string>
#include <core_info.h>

using std::cout;
using std::endl;
using std::string;

void PrintVersion()
{
	cout << GAME_NAME << " " << GAME_VERSION << endl;
	cout << GAME_DESCRIPTION << endl;
	cout << "Author: " << AUTHOR << " (" << AUTHOR_EMAIL << ")" << endl;
}

/*
 * @brief Print the usage message of the program.
 *
 * labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]
 */
void PrintUsage()
{
	cout << "Usage: "
		 << PROGRAM_NAME
		 << " [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]"
		 << endl;

	cout << "Options:" << endl;
	cout << "  -m, --map FILE    Specify the map file to use" << endl;

	cout << "  -p, --player ID    Specify the player ID to use" << endl;

	cout << "      --move DIRECTION (up, down, left, right)    Specify the direction to move" << endl;

	cout << "      --version    Show the version information" << endl;

	cout << "  -h, --help    Show this help message" << endl;

	cout << "Tips:" << endl
		 << "  1. '-p' '-m' can exchange their positions" << endl
		 << "  2. '--move' must be used with '-p'" << endl;
}

int main(int argc, char *argv[])
{
	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"player", required_argument, nullptr, 'p'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 0},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	string map_file;
	string player_id;
	string move_direction;

	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			cout << "Map file: " << optarg << endl;
			break;
		case 'p':
			cout << "Player ID: " << optarg << endl;
			break;
		case 0:
			if (long_index == 2)
			{
				cout << "Move direction: " << optarg << endl;
			}
			else if (long_index == 3)
			{
				PrintVersion();
			}
			break;
		case 'h':
			PrintUsage();
			return 0;
		case '?':
			if (optopt == 'm' || optopt == 'p')
			{
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			}
			else if (isprint(optopt))
			{
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			}
			else
			{
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			}
			return 1;
		default:
			PrintUsage();
			return 1;
		}
	}

	// 检查必需参数是否提供
	if (map_file.empty() ^ player_id.empty())
	{
		fprintf(stderr, "Map file and player ID are required.\n");
		return 1;
	}

	return 0;
}

UnitTest(TestPrintVersion)
{
	PrintVersion();
}

UnitTest(TestPrintUsage)
{
	PrintUsage();
}