#pragma once
#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <string>
#include <debug_run.h>

class LogLevel
{
public:
	enum Value : int
	{
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR,
		LOG_LEVEL_COUNT,
	};

	constexpr LogLevel(Value value) : value_(value) {}

	int toInt() const
	{
		return static_cast<int>(value_);
	}
	Value value() const { return value_; }

	// 内置字符串转换功能
	std::string toString() const;
	std::string toMessage() const;
	const char *toCString() const;

	operator LogLevel::Value() const
	{
		return value_;
	}

private:
	Value value_;
};

void DebugLog_(LogLevel level, const std::string &file, int line, const std::string &format, ...);

#define DebugLog(level, format, ...) DebugRun(DebugLog_(level, __FILE__, __LINE__, format, ##__VA_ARGS__))

#endif //! DEBUG_LOG_H