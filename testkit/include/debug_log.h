#pragma once
#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <string>
#include <debug_run.h>

enum class LogLevel : int
{
	DEBUG = 0,
	INFO,
	WARNING,
	ERROR,
	LOG_LEVEL_COUNT,
};

void DebugLog_(LogLevel level, const std::string &file, int line, const std::string &format, ...);

#define DebugLog(level, format, ...) DebugRun(DebugLog_(level, __FILE__, __LINE__, format, ##__VA_ARGS__))

#endif //! DEBUG_LOG_H