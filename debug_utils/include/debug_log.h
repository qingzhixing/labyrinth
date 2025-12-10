#pragma once
#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <string>
#include <debug_run.h>

class LogLevel
{
public:
	enum LogLevelValue : int
	{
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR,
		LOG_LEVEL_COUNT,
	};

	constexpr LogLevel(LogLevelValue value) : value(value) {}

	int toInt() const
	{
		return static_cast<int>(value);
	}
	LogLevelValue GetValue() const { return value; }

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;

	operator LogLevel::LogLevelValue() const
	{
		return value;
	}

private:
	LogLevelValue value;
};

void DebugLog_(LogLevel level, const std::string &file, int line, const std::string &format, ...);

#define DebugLog(level, format, ...) DebugRun(DebugLog_(level, __FILE__, __LINE__, format, ##__VA_ARGS__))

#endif //! DEBUG_LOG_H