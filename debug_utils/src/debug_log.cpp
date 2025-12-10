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
	switch (value_)
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

const char *LogLevel::toCString() const
{
	return toString().c_str();
}

void DebugLog_(LogLevel level, const std::string &file, int line, const std::string &format, ...)
{
	// Only log when debug logging is enabled.
	if (!getenv(DBG_LOG_ENABLE))
	{
		return;
	}
	va_list args;
	va_start(args, format);
	char message[1024];
	vsnprintf(message, sizeof(message), format.c_str(), args);
	va_end(args);

	cout << "[" << file << ":" << line << "] "
		 << level.toString()
		 << ": "
		 << message << endl;
}