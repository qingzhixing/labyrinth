#include <iostream>
#include <testkit.h>
#include <debug_run.h>
#include <game_info.h>
#include <format>

using std::cin;
using std::cout;
using std::endl;

void PrintGameInfo()
{
	cout << GAME_NAME_ASCII_ART << endl;
	cout << std::format("Welcome to {} ({})", GAME_NAME, GAME_VERSION) << endl;
	cout << std::format("Author: {} <{}>", AUTHOR, AUTHOR_EMAIL) << endl;
}

void DisplayGameMap() {}
void ReadUserInput() {}
void CallCoreExecutable() {}
void CheckGameEnd() {}

int main(int argc, char *argv[])
{
	PrintGameInfo();
	DisplayGameMap();
	ReadUserInput();
	CallCoreExecutable();
	CheckGameEnd();
	return 0;
}