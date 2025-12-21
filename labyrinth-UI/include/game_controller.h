#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <types/direction.h>
#include <types/error_code.h>

class GameController
{
public:
	GameController(std::string core_executable_path, std::string map_file_path);

public:
	ErrorCode MovePlayer(Direction direction) const;
	std::pair<bool, ErrorCode> IsGameEnd() const;
	ErrorCode PrintMap() const;
	void SetMapFilePath(const std::string &map_file_path);
	ErrorCode ValidateMap() const;

private:
	std::string core_executable_path;
	std::string map_file_path;
};

#endif // GAME_CONTROLLER_H
