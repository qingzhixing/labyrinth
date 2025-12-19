#include <debug_log.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
#include <debug_flags.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

std::string LogLevel::toString() const
{
	switch (value)
	{
	case DEBUG:
		return "DEBUG";
	case INFO:
		return "INFO";
	case WARNING:
		return "WARNING";
	case ERROR:
		return "ERROR";
	case LOG_LEVEL_COUNT:
		return "LOG_LEVEL_COUNT";
	default:
		return "Invalid Log Level: " + std::to_string(toInt());
	}
}

std::string LogLevel::toMessage() const
{
	return "LogLevel: " +
		   std::to_string(toInt()) +
		   ", Name: " +
		   toString();
}

bool IsDebugLogNotEnabled()
{
	// Only log when debug logging is enabled.
	return getenv(DBG_LOG_ENABLE) == nullptr;
}

void DebugLog_(LogLevel level, const std::string &file, int row, const std::string &format, ...)
{
	if (IsDebugLogNotEnabled())
	{
		return;
	}
	va_list args;
	va_start(args, format);
	char message[1024];
	vsnprintf(message, sizeof(message), format.c_str(), args);
	va_end(args);

	cout << "[" << file << ":" << row << "] "
		 << level.toString()
		 << ": "
		 << message << endl;
}