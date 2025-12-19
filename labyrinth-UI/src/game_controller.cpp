#include <game_controller.h>
#include <core_caller.h>
#include <iostream>
#include <fstream>
#include <types/map_cell.h>

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

bool GameController::IsGameEnd() const
{
	std::fstream map_file(map_file_path);
	char ch;
	while (map_file.get(ch))
	{
		if (ch == GetMapCellChar(MapCellType::PLAYER_AT_DESTINATION))
		{
			return true;
		}
	}
	return false;
}

void GameController::PrintMap() const
{
	std::fstream map_file(map_file_path);
	char ch;
	while (map_file.get(ch))
	{
		std::cout << ch;
	}
}
