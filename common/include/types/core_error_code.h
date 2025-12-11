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
		INVALID_PLAYER_ID,
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

	constexpr GameCoreErrorCode(ErrorCodeValue value) : value(value) {}

	int toInt() const
	{
		return static_cast<int>(value);
	}
	ErrorCodeValue GetValue() const { return value; }

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;

	operator GameCoreErrorCode::ErrorCodeValue() const
	{
		return value;
	}

private:
	ErrorCodeValue value;
};

#endif // GAME_CORE_ERROR_CODE_H