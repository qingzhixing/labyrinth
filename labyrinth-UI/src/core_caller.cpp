#include <core_caller.h>
#include <filesystem>
#include <cstring>
#include <unistd.h>
#include <debug_log.h>
#include <sys/time.h>
#include <sys/wait.h>

ErrorCode
CoreCaller::CallCoreExecutable(
	const std::string &core_executable_path,
	const std::vector<std::string> &arguments)
{
	auto error_code = ValidateCoreExecutable(core_executable_path);
	if (error_code != ErrorCode::SUCCESS)
	{
		return error_code;
	}

	// Call core executable
	// Copy arguments
	char **argv = new char *[arguments.size() + 2];
	// Copy core executable path
	argv[0] = strdup(core_executable_path.c_str());
	for (size_t i = 0; i < arguments.size(); ++i)
	{
		argv[i + 1] = strdup(arguments[i].c_str());
	}
	argv[arguments.size() + 1] = nullptr;

	pid_t pid = fork();
	if (pid < 0)
	{
		DebugLog(LogLevel::ERROR, "fork failed: %s", strerror(errno));
		return ErrorCode::CORE_EXECUTION_FAILED;
	}
	else if (pid == 0)
	{
		// Child process
		// set Timeout: 3s
		struct itimerval timeout;
		timeout.it_value.tv_sec = 3; // 3 seconds timeout
		timeout.it_value.tv_usec = 0;
		timeout.it_interval.tv_sec = 0;
		timeout.it_interval.tv_usec = 0;

		if (setitimer(ITIMER_REAL, &timeout, nullptr) < 0)
		{
			DebugLog(LogLevel::ERROR, "setitimer failed: %s", strerror(errno));
			exit(ErrorCode::CORE_TIME_OUT);
		}
		execvp(("./" + core_executable_path).c_str(), argv);
		// If execvp returns, it must have failed
		DebugLog(LogLevel::ERROR, "execvp failed: %s", strerror(errno));
		exit(ErrorCode::CORE_EXECUTION_FAILED);
	}
	else
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		// 获取ErrorCode
		if (WIFEXITED(status))
		{
			return ErrorCode(WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			return ErrorCode::CORE_EXECUTION_FAILED;
		}
		else
		{
			return ErrorCode::CORE_EXECUTION_FAILED;
		}
	}
}

ErrorCode CoreCaller::ValidateCoreExecutable(const std::string &core_executable_path)
{
	if (!std::filesystem::exists(core_executable_path))
	{
		return ErrorCode::CORE_NOT_FOUND;
	}

	if (!std::filesystem::is_regular_file(core_executable_path))
	{
		return ErrorCode::CORE_NOT_FOUND;
	}

	// Not executable
	if ((std::filesystem::status(core_executable_path).permissions() &
		 std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
	{
		return ErrorCode::CORE_NOT_EXECUTABLE;
	}

	return ErrorCode::SUCCESS;
}
