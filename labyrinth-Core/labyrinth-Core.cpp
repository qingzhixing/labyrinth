#include <iostream>
#include <testkit.h>
#include <getopt.h>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
 * @brief Print the usage message of the program.
 *
 * @param programName The name of the program.
 *
 * labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]
 */
void PrintUsage(const string &programName)
{
	cout << "Usage: "
		 << programName
		 << " [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]"
		 << endl;

	cout << "Options:" << endl;
	cout << "  -m, --map FILE    Specify the map file to use" << endl;
	cout << "  -p, --player ID    Specify the player ID to use" << endl;
	cout << "      --move DIRECTION    Specify the direction to move" << endl;
	cout << "      --version    Show the version information" << endl;
	cout << "  -h, --help    Show this help message" << endl;
}

int main(int argc, char *argv[])
{
	PrintUsage("labyrinth-Core");
	return 0;
}