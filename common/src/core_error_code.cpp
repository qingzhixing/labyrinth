#include <core_error_code.h>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const std::string GetGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	static const vector<string> ErrorCodeMessages{
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
	;

	int code = error_code;
	int error_code_count = GameCoreErrorCode::GAME_CORE_ERROR_CODE_COUNT;

	if (code < 0 || code >= error_code_count)
	{
		return "Invalid error code: " + std::to_string(code);
	}
	return ErrorCodeMessages.at(code);
}

void PrintGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	cout << "GameCoreErrorCode: " << error_code << ", Message: " << GetGameCoreErrorMessage(error_code) << endl;
}