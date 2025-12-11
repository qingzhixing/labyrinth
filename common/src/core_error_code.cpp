#include <types/core_error_code.h>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

std::string GameCoreErrorCode::toString() const
{
	switch (value)
	{
	case SUCCESS:
		return "Success [成功]";
	case MAP_FILE_NOT_FOUND:
		return "Map file not found [地图文件未找到]";
	case INVALID_MAP_FORMAT:
		return "Invalid map format [地图格式无效]";
	case MAP_FILE_IS_DIRECTORY:
		return "Map is a directory [地图文件是一个目录]";
	case MAP_TOO_LARGE:
		return "Map too large [地图过大]";
	case MAP_INCONSISTENT_LINE:
		return "Map inconsistent line [地图行不一致]";
	case MAP_NO_DESTINATION:
		return "Map no destination '@' found [地图无终点]";
	case INVALID_PLAYER_ID:
		return "Invalid player ID [玩家ID无效]";
	case INVALID_MOVE_DIRECTION:
		return "Invalid move direction [移动方向无效]";
	case MISSING_PARAMETERS:
		return "Missing parameters [缺失参数]";
	case EXCESSIVE_PARAMETERS:
		return "Excessive parameters [多余参数]";
	case INVALID_PARAMETERS:
		return "Invalid parameters [无效参数]";
	case MOVE_FAILED:
		return "Move failed [移动失败]";
	case HELP_REQUESTED:
		return "Help requested [请求帮助]";
	case VERSION_REQUESTED:
		return "Version requested [请求版本]";
	case DEFAULT_ERROR_CODE:
		return "Default error code, This Should Not Happen [默认错误码,通常情况下不应该会返回！！！]";
	default:
		return "Invalid error code: " + std::to_string(toInt());
	}
}

std::string GameCoreErrorCode::toMessage() const
{
	return "GameCoreErrorCode: " +
		   std::to_string(toInt()) +
		   ", Message: " +
		   toString();
}