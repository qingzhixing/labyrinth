#pragma once
#ifndef CORE_CALLER_H
#define CORE_CALLER_H

#include <string>
#include <types/core_error_code.h>
#include <vector>
#include <game_info.h>

class CoreCaller
{
public:
	static GameCoreErrorCode CallCoreExecutable(
		const std::string &core_executable_path,
		const std::vector<std::string> &arguments);

	static bool ValidateCoreExecutable(const std::string &core_executable_path);
};

#endif // CORE_CALLER_H