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
	cout << "      --move DIRECTION    Specify the direction to move" << endl;
	cout << "      --version    Show the version information" << endl;
	cout << "  -h, --help    Show this help message" << endl;
	cout << "Tips: '-p' '-m' can exchange their positions" << endl;
}

int main(int argc, char *argv[])
{
	return 0;
}

UnitTest(TestPrintVersion)
{
	cout << "TestPrintVersion:" << endl;
	PrintVersion();
}

UnitTest(TestPrintUsage)
{
	cout << "TestPrintUsage:" << endl;
	PrintUsage();
}