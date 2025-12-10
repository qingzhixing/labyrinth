#include <core_error_code.h>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const std::string GameCoreErrorCodeStr(GameCoreErrorCode error_code)
{
	static const vector<string> ErrorCodeMessages{
		"Success [成功]",
		"Map file not found [地图文件未找到]",
		"Invalid map format [地图格式无效]",
		"Map too large [地图过大]",
		"Invalid player ID [玩家ID无效]",
		"Invalid move direction [移动方向无效]",
		"Missing parameters [缺失参数]",
		"Excessive parameters [多余参数]",
		"Invalid parameters [无效参数]",
		"Move failed [移动失败]",
		"Help requested [请求帮助]",
		"Default error code, This Should Not Happen [默认错误码,通常情况下不应该会返回！！！]",
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

string GetGameCoreErrorMessage(GameCoreErrorCode error_code)
{
	return "GameCoreErrorCode: " +
		   std::to_string(error_code) +
		   ", Message: " +
		   GameCoreErrorCodeStr(error_code);
}