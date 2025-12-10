#pragma once
#ifndef GAME_CORE_ERROR_CODE_H
#define GAME_CORE_ERROR_CODE_H

#include <string>

class GameCoreErrorCode
{
public:
	enum Value : int
	{
		SUCCESS = 0,
		MAP_NOT_FOUND,
		INVALID_MAP_FORMAT,
		MAP_TOO_LARGE,
		INVALID_PLAYER_ID,
		INVALID_MOVE_DIRECTION,
		INVALID_PARAMETERS,
		MISSING_PARAMETERS,
		EXCESSIVE_PARAMETERS,
		MOVE_FAILED,
		HELP_REQUESTED,

		DEFAULT_ERROR_CODE,

		GAME_CORE_ERROR_CODE_COUNT,
	};

	constexpr GameCoreErrorCode(Value value) : value_(value) {}

	int toInt() const
	{
		return static_cast<int>(value_);
	}
	Value value() const { return value_; }

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;
	const char *toCString() const;

	operator GameCoreErrorCode::Value() const
	{
		return value_;
	}

private:
	Value value_;
};

#endif // GAME_CORE_ERROR_CODE_H