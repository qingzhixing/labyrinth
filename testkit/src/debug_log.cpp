#include <debug_log.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const string &GetLogLevelName(LogLevel level)
{
	static const std::vector<string> levelNames{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"LOG_LEVEL_COUNT",
	};

	int level_int = static_cast<int>(level);
	int log_level_count = static_cast<int>(LogLevel::LOG_LEVEL_COUNT);

	if (level_int >= 0 &&
		level_int < log_level_count)
	{
		return levelNames.at(level_int);
	}
	else
	{
		return "Invalid Log Level: " + std::to_string(static_cast<int>(level));
	}
}

void DebugLog_(LogLevel level, const std::string &file, int line, const std::string &format, ...)
{
	va_list args;
	va_start(args, format);
	char message[1024];
	vsnprintf(message, sizeof(message), format.c_str(), args);
	va_end(args);

	cout << "[" << file << ":" << line << "] "
		 << GetLogLevelName(level)
		 << ": "
		 << message << endl;
}