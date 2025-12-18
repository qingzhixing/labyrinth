#pragma once
#ifndef CORE_CALLER_H
#define CORE_CALLER_H

#include <string>
#include <types/error_code.h>
#include <vector>
#include <game_info.h>

class CoreCaller
{
public:
	static ErrorCode CallCoreExecutable(
		const std::string &core_executable_path,
		const std::vector<std::string> &arguments);

	static ErrorCode ValidateCoreExecutable(const std::string &core_executable_path);
};

#endif // CORE_CALLER_H