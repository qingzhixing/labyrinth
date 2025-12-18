#pragma once
#ifndef CORE_CALLER_H
#define CORE_CALLER_H

#include <string>
#include <types/error_code.h>
#include <vector>

class CoreCaller
{
public:
	static ErrorCode CallCoreExecutable(
		const std::string &core_executable_path,
		const std::vector<std::string> &arguments);

	static ErrorCode ValidateCoreExecutable(const std::string &core_executable_path);

	static char **ConvertArgumentsToCharPtrArray(const std::vector<std::string> &arguments);

	static void FreeArgumentsArray(char **argv, size_t argument_count);

private:
	static void ExecuteChildProcess(const std::string &core_executable_path,
									char **argv, size_t argument_count);

	static ErrorCode WaitForChildProcess(pid_t pid, char **argv, size_t argument_count);

	static ErrorCode ProcessChildExitStatus(int status);
};

#endif // CORE_CALLER_H