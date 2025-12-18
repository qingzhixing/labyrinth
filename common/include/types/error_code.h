#pragma once
#ifndef GAME_CORE_ERROR_CODE_H
#define GAME_CORE_ERROR_CODE_H

#include <string>

class ErrorCode
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
		CORE_NOT_FOUND,
		CORE_TIME_OUT,
		CORE_NOT_EXECUTABLE,
		CORE_EXECUTION_FAILED,

		DEFAULT_ERROR_CODE,

		GAME_CORE_ERROR_CODE_COUNT,
	};

	ErrorCode(ErrorCodeValue value);

	explicit ErrorCode(int value);

	int toInt() const;
	ErrorCodeValue GetValue() const;

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;

	operator ErrorCode::ErrorCodeValue() const;

private:
	ErrorCodeValue value;
};

#endif // GAME_CORE_ERROR_CODE_H