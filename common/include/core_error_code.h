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
		GAME_CORE_ERROR_CODE_MAX,
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
};

std::string GetGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	int code = error_code; // 隐式转换
	if (code < 0 || code >= GameCoreErrorCode::GAME_CORE_ERROR_CODE_MAX)
	{
		return "Unknown error";
	}
	return GameCoreErrorMessages[code];
}