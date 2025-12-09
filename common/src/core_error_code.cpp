#include <core_error_code.h>

std::string GetGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	int code = error_code; // 隐式转换
	if (code < 0 || code >= GameCoreErrorCode::GAME_CORE_ERROR_CODE_MAX)
	{
		return "Unknown error";
	}
	return GameCoreErrorMessages[code];
}
