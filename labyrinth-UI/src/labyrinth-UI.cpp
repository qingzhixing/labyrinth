#include <iostream>
#include <testkit.h>
#include <debug_run.h>
#include <game_info.h>
#include <format>
#include <game_controller.h>
#include <debug_log.h>
#include <environment.h>

using std::cin;
using std::cout;
using std::endl;

void PrintGameInfo()
{
	cout << GAME_NAME_ASCII_ART << endl;
	cout << std::format("Welcome to {} ({})", GAME_NAME, GAME_VERSION) << endl;
	cout << std::format("Author: {} <{}>", AUTHOR, AUTHOR_EMAIL) << endl;
}

static GameController game_controller(
	("./" + GAME_CORE_EXECUTABLE_NAME),
	"./map.txt");

ErrorCode DisplayGameMap()
{
	DebugLog(LogLevel::INFO, "Display game map");
	cout << "Game Map:" << endl;
	auto result = game_controller.PrintMap();
	cout << endl;
	return result;
}

void ReadUserInput() {}

ErrorCode CallCoreExecutable()
{
	DebugLog(LogLevel::INFO, "Call core executable");
	return game_controller.MovePlayer(Direction::DOWN);
}

bool CheckGameEnd()
{
	DebugLog(LogLevel::INFO, "Check game end");
	auto [is_game_end, error_code] = game_controller.IsGameEnd();
	if (error_code != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, error_code.toMessage());
	}
	return is_game_end;
}

int main(int argc, char *argv[])
{
	PrintGameInfo();

	// 如果在测试环境则不进入游戏主逻辑
	if (IsTestEnvironment())
	{
		return 0;
	}

	while (!CheckGameEnd())
	{
		auto display_result = DisplayGameMap();
		if (display_result != ErrorCode::SUCCESS)
		{
			cout << display_result.toMessage() << endl;
			break;
		}

		ReadUserInput();

		auto move_result = CallCoreExecutable();
		if (move_result != ErrorCode::SUCCESS)
		{
			cout << move_result.toMessage() << endl;
			break;
		}
	}
	return 0;
}