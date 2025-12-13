#pragma once
#ifndef GAME_CORE_ERROR_CODE_H
#define GAME_CORE_ERROR_CODE_H

#include <string>

class GameCoreErrorCode
{
public:
	enum ErrorCodeValue : int
	{
		SUCCESS = 0,
		MAP_FILE_NOT_FOUND,
		MAP_TOO_LARGE,
		INVALID_MAP_FORMAT,
		MAP_FILE_IS_DIRECTORY,
		MAP_INCONSISTENT_LINE,
		MAP_NO_DESTINATION,
		MAP_MULTIPLE_DESTINATION,
		MAP_MULTIPLE_PLAYER,
		INVALID_MOVE_DIRECTION,
		INVALID_PARAMETERS,
		MISSING_PARAMETERS,
		EXCESSIVE_PARAMETERS,
		MOVE_FAILED,
		HELP_REQUESTED,
		VERSION_REQUESTED,

		DEFAULT_ERROR_CODE,

		GAME_CORE_ERROR_CODE_COUNT,
	};

	GameCoreErrorCode(ErrorCodeValue value);

	int toInt() const;
	ErrorCodeValue GetValue() const;

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;

	operator GameCoreErrorCode::ErrorCodeValue() const;

private:
	ErrorCodeValue value;
};

#endif // GAME_CORE_ERROR_CODE_H