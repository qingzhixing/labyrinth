#include <game_controller.h>
#include <core_caller.h>
#include <iostream>
#include <fstream>
#include <types/map_cell.h>
#include <utility>
#include <debug_log.h>

GameController::GameController(std::string core_executable_path, std::string map_file_path)
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

std::pair<bool, ErrorCode> GameController::IsGameEnd() const
{
	std::fstream map_file(map_file_path);

	if (!map_file.is_open())
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file %s", map_file_path.c_str());
		return std::make_pair(false, ErrorCode::MAP_FILE_OPEN_FAILED);
	}

	char ch;
	while (map_file.get(ch))
	{
		if (ch == GetMapCellChar(MapCellType::PLAYER_AT_DESTINATION))
		{
			DebugLog(LogLevel::INFO, "Player is at destination");
			return std::make_pair(true, ErrorCode::SUCCESS);
		}
	}

	DebugLog(LogLevel::INFO, "Player is not at destination");
	return std::make_pair(false, ErrorCode::SUCCESS);
}

ErrorCode GameController::PrintMap() const
{
	std::ifstream map_file(map_file_path);
	// 检查文件是否成功打开
	if (!map_file.is_open())
	{
		DebugLog(LogLevel::ERROR, "Failed to open map file %s", map_file_path.c_str());
		return ErrorCode::MAP_FILE_OPEN_FAILED;
	}

	char ch;
	while (map_file.get(ch))
	{
		std::cout << ch;
	}
	return ErrorCode::SUCCESS;
}
