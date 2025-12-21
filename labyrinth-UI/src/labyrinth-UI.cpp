#include <iostream>
#include <testkit.h>
#include <debug_run.h>
#include <game_info.h>
#include <format>
#include <game_controller.h>
#include <debug_log.h>
#include <environment.h>
#include <map_chooser.h>
#include <ui_utilities.h>

using std::cin;
using std::cout;
using std::endl;

void PrintGameInfo()
{
	cout << GAME_NAME_ASCII_ART << endl;
	cout << std::format("Welcome to {} ({}).", GAME_NAME, GAME_VERSION) << endl;
	cout << std::format("Author: {} <{}>", AUTHOR, AUTHOR_EMAIL) << endl;
	cout << "'0' -> Player." << endl;
	cout << "'@' -> Destination." << endl;
	cout << "'#' -> Wall." << endl;
	cout << "'.' -> Space." << endl;
	cout << "'W' -> Player at destination." << endl;
}

static GameController game_controller(
	("./" + GAME_CORE_EXECUTABLE_NAME),
	"./map.txt");

ErrorCode DisplayGameMap()
{
	DebugLog(LogLevel::INFO, "Display game map");
	cout << endl;
	auto result = game_controller.PrintMap();
	cout << endl;
	return result;
}

std::pair<bool, Direction> ReadUserInput()
{
	DebugLog(LogLevel::INFO, "Read user input");
	cout << "Please input your move (w/a/s/d; q to quit): ";
	char input;
	cin >> input;
	switch (input)
	{
	case 'w':
		return std::make_pair(true, Direction::UP);
	case 'a':
		return std::make_pair(true, Direction::LEFT);
	case 's':
		return std::make_pair(true, Direction::DOWN);
	case 'd':
		return std::make_pair(true, Direction::RIGHT);
	case 'q':
		return std::make_pair(true, Direction::INVALID);
	default:
		DebugLog(LogLevel::ERROR, "Invalid input");
		return std::make_pair(false, Direction::INVALID);
	}
}

ErrorCode CallCoreExecutable(Direction direction)
{
	DebugLog(LogLevel::INFO, "Call core executable");
	return game_controller.MovePlayer(direction);
}

bool IsGameEnd()
{
	DebugLog(LogLevel::INFO, "Check game end");
	auto [is_game_end, error_code] = game_controller.IsGameEnd();
	if (error_code != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, error_code.toMessage());
	}
	return is_game_end;
}

bool NeedNextGame()
{
	DebugLog(LogLevel::INFO, "Check need next game");
	cout << "是否需要继续下一局游戏? (y/n)" << endl;
	char input;
	cin >> input;
	input = std::tolower(input);
	return input == 'y';
}

bool GameLogic()
{
	// 选择地图
	auto [map_file_path, success] = ChooseMap();
	if (!success)
	{
		cout << "地图选择中断!" << endl;
		return NeedNextGame();
	}
	game_controller.SetMapFilePath(map_file_path);

	bool quit_game = false;

	if (IsGameEnd())
	{
		cout << "地图已到达终点!" << endl;
		DisplayGameMap();
		return NeedNextGame();
	}

	while (!quit_game)
	{
		ClearScreen();

		PrintGameInfo();

		auto display_result = DisplayGameMap();
		if (display_result != ErrorCode::SUCCESS)
		{
			cout << display_result.toMessage() << endl;
			return 0;
		}

		// Check for win
		if (IsGameEnd())
		{
			cout << "You win!" << endl;
			break;
		}

		auto [is_valid, direction] = ReadUserInput();

		// Check for quit
		if (direction == Direction::INVALID && is_valid)
		{
			quit_game = true;
			continue;
		}

		// 输入非法, 继续读取
		if (!is_valid)
		{
			continue;
		}

		auto move_result = CallCoreExecutable(direction);

		if (move_result != ErrorCode::SUCCESS &&
			move_result != ErrorCode::MOVE_FAILED)
		{
			cout << move_result.toMessage() << endl;
			return 0;
		}
	}

	// Check for quit
	if (quit_game)
	{
		cout << "Quit game." << endl;
	}

	return NeedNextGame();
}

int main(int argc, char *argv[])
{
	// 如果在测试环境则不进入游戏主逻辑
	if (IsTestEnvironment())
	{
		return 0;
	}

	while (GameLogic())
	{
		// Do Nothing
	}

	return 0;
}