#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <types/direction.h>
#include <types/error_code.h>

class GameController
{
public:
	GameController();
	~GameController();

public:
	ErrorCode MovePlayer(Direction direction) const;
	bool IsGameEnd() const;
	ErrorCode PrintMap() const;

private:
	std::string core_executable_path;
	std::string map_file_path;
};

#endif // GAME_CONTROLLER_H
