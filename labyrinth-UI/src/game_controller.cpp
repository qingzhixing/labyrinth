#include <game_controller.h>
#include <core_caller.h>
#include <iostream>
#include <fstream>
#include <types/map_cell.h>
#include <utility>
#include <vector>
#include <debug_log.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

GameController::GameController(string core_executable_path, string map_file_path)
{
	this->core_executable_path = core_executable_path;
	this->map_file_path = map_file_path;
}

ErrorCode GameController::MovePlayer(Direction direction) const
{
	return CoreCaller::CallCoreExecutable(
		core_executable_path,
		{"--map",
		 map_file_path,
		 "--move",
		 DirectionToString(direction)});
}

pair<bool, ErrorCode> GameController::IsGameEnd() const
{
	ifstream map_file(map_file_path);

	if (!map_file.is_open())
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file %s", map_file_path.c_str());
		return make_pair(false, ErrorCode::MAP_FILE_OPEN_FAILED);
	}

	char ch;
	while (map_file.get(ch))
	{
		if (ch == GetMapCellChar(MapCellType::PLAYER_AT_DESTINATION))
		{
			DebugLog(LogLevel::INFO, "Player is at destination");
			return make_pair(true, ErrorCode::SUCCESS);
		}
	}

	DebugLog(LogLevel::INFO, "Player is not at destination");
	return make_pair(false, ErrorCode::SUCCESS);
}

ErrorCode GameController::PrintMap() const
{
	ifstream map_file(map_file_path);
	// 检查文件是否成功打开
	if (!map_file.is_open())
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file %s", map_file_path.c_str());
		return ErrorCode::MAP_FILE_OPEN_FAILED;
	}

	// 读取地图文件
	vector<string> map_lines;
	int row = 0, column = 0;
	string single_line;
	while (std::getline(map_file, single_line))
	{
		map_lines.push_back(single_line);
		column = single_line.size();
		row++;
	}

	// 打印地图并添加边框('+' '-' '|')
	// 打印顶部边框
	cout << "+";
	for (int i = 0; i < column; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	for (int i = 0; i < row; i++)
	{
		cout << "|";
		cout << map_lines[i];
		cout << "|" << endl;
	}

	// 打印底部边框
	cout << "+";
	for (int i = 0; i < column; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	return ErrorCode::SUCCESS;
}

void GameController::SetMapFilePath(const string &map_file_path)
{
	this->map_file_path = map_file_path;
}

ErrorCode GameController::GetMapValidatedErrorCode() const
{
	return ValidateMap(core_executable_path, map_file_path);
}

ErrorCode GameController::ValidateMap(const string &core_executable_path, const string &map_file_path)
{
	return CoreCaller::CallCoreExecutable(
		core_executable_path,
		{"--map", map_file_path,
		 "--move", "up",
		 "--validate"});
}
