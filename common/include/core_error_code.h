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
		MISSING_PARAMETERS,
		EXCESSIVE_PARAMETERS,
		INVALID_PARAMETERS,
		MOVE_FAILED,
		HELP_REQUESTED,

		DEFAULT_ERROR_CODE,

		GAME_CORE_ERROR_CODE_COUNT,
	};

	constexpr GameCoreErrorCode(Value value) : value_(value) {}

	operator int() const
	{
		return static_cast<int>(value_);
	}
	Value value() const { return value_; }

private:
	Value value_;
};

static const std::string GameCoreErrorMessages[] = {
	"Success",
	"Map file not found",
	"Invalid map format",
	"Map too large",
	"Invalid player ID",
	"Invalid move direction",
	"Missing parameters",
	"Excessive parameters",
	"Invalid parameters",
	"Move failed",
	"Help requested",
	"Default error code",
};

/**
 * @brief Get the Game Core Error Message object
 *
 * @param error_code
 * @return std::string	Error message corresponding to the error code
 */
std::string GetGameCoreErrorMessage(GameCoreErrorCode error_code);

#endif // GAME_CORE_ERROR_CODE_H
