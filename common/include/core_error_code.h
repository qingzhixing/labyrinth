#include <string>

enum GameCoreErrorCode
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

	GAME_CORE_ERROR_CODE_MAX,
};

static const std::string GameCoreErrorMessages[GAME_CORE_ERROR_CODE_MAX] = {
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
};

std::string GetGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	if (error_code < 0 || error_code >= GAME_CORE_ERROR_CODE_MAX)
	{
		return "Unknown error";
	}
	return GameCoreErrorMessages[error_code];
}