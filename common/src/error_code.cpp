#include <types/error_code.h>
#include <string>

ErrorCode::ErrorCode(ErrorCodeValue value) : value(value) {}

ErrorCode::ErrorCode(int value)
{
	this->value = static_cast<ErrorCodeValue>(value);
}

int ErrorCode::toInt() const
{
	return static_cast<int>(value);
}

ErrorCode::ErrorCodeValue ErrorCode::GetValue() const
{
	return value;
}

ErrorCode::operator ErrorCode::ErrorCodeValue() const
{
	return value;
}

std::string ErrorCode::toString() const
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
	case MAP_INCONSISTENT_ROW:
		return "Map inconsistent row [地图行不一致]";
	case MAP_NO_DESTINATION:
		return "Map no destination '@' found [地图无终点]";
	case MAP_MULTIPLE_DESTINATION:
		return "Map multiple destination '@' found [地图有多个终点]";
	case MAP_MULTIPLE_PLAYER:
		return "Map multiple player '0' found [地图有多个玩家]";
	case MAP_FILE_OPEN_FAILED:
		return "Map file open failed [地图文件打开失败]";
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
	case CORE_NOT_FOUND:
		return "Core executable not found [Core 文件未找到]";
	case CORE_TIME_OUT:
		return "Core executable time out [Core 运行超时]";
	case CORE_NOT_EXECUTABLE:
		return "Core executable not executable [Core 文件不可执行]";
	case CORE_EXECUTION_FAILED:
		return "Core executable execution failed [Core 文件执行失败]";
	case DEFAULT_ERROR_CODE:
		return "Default error code, This Should Not Happen [默认错误码,通常情况下不应该会返回！！！]";
	default:
		return "Invalid error code: " + std::to_string(toInt());
	}
}

std::string ErrorCode::toMessage() const
{
	return "ErrorCode: " +
		   std::to_string(toInt()) +
		   ", Message: " +
		   toString();
}