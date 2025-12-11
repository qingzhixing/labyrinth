#include <core_info.h>
#include <iostream>

using std::cout;
using std::endl;

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
		 << " [-m|--map FILE] [--move DIRECTION] [-v|--version]"
		 << endl;

	cout << "Options:" << endl;
	cout << "  -m, --map FILE    Specify the map file to use" << endl;

	cout << "      --move DIRECTION (up, down, left, right)    Specify the direction to move" << endl;

	cout << "  -v, --version    Show the version information" << endl;

	cout << "  -h, --help    Show this help message" << endl;

	cout << "Tips:" << endl
		 << "  1. '--move' '-m' must be used together" << endl;
}