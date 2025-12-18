#include <core_caller.h>
#include <debug_log.h>
#include <filesystem>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
ErrorCode CoreCaller::CallCoreExecutable(
	const std::string &core_executable_path,
	const std::vector<std::string> &arguments)
{
	// 验证可执行文件
	auto error_code = ValidateCoreExecutable(core_executable_path);
	if (error_code != ErrorCode::SUCCESS)
	{
		return error_code;
	}

	// 准备参数
	auto new_arguments = arguments;
	new_arguments.insert(new_arguments.begin(), core_executable_path);
	char **argv = ConvertArgumentsToCharPtrArray(new_arguments);

	// 创建子进程
	pid_t pid = fork();
	if (pid < 0)
	{
		DebugLog(LogLevel::ERROR, "fork failed: %s", strerror(errno));
		FreeArgumentsArray(argv, new_arguments.size());
		return ErrorCode::CORE_EXECUTION_FAILED;
	}

	if (pid == 0)
	{
		// 子进程：执行核心程序
		ExecuteChildProcess(core_executable_path, argv, new_arguments.size());
	}
	else
	{
		// 父进程：等待子进程结束
		error_code = WaitForChildProcess(pid, argv, new_arguments.size());
	}

	return error_code;
}

ErrorCode CoreCaller::ValidateCoreExecutable(const std::string &core_executable_path)
{
	// 检查文件是否存在
	if (!std::filesystem::exists(core_executable_path))
	{
		return ErrorCode::CORE_NOT_FOUND;
	}

	// 检查是否为普通文件
	if (!std::filesystem::is_regular_file(core_executable_path))
	{
		return ErrorCode::CORE_NOT_FOUND;
	}

	// 检查执行权限
	if ((std::filesystem::status(core_executable_path).permissions() &
		 std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
	{
		return ErrorCode::CORE_NOT_EXECUTABLE;
	}

	return ErrorCode::SUCCESS;
}

char **CoreCaller::ConvertArgumentsToCharPtrArray(const std::vector<std::string> &arguments)
{
	char **argv = new char *[arguments.size() + 1];

	for (size_t i = 0; i < arguments.size(); ++i)
	{
		argv[i] = strdup(arguments[i].c_str());
	}
	argv[arguments.size()] = nullptr;

	return argv;
}

void CoreCaller::FreeArgumentsArray(char **argv, size_t argument_count)
{
	if (argv)
	{
		for (size_t i = 0; i < argument_count; ++i)
		{
			free(argv[i]);
		}
		delete[] argv;
	}
}

void CoreCaller::ExecuteChildProcess(const std::string &core_executable_path,
									 char **argv, size_t argument_count)
{
	// 设置超时定时器（3秒）
	struct itimerval timeout;
	timeout.it_value.tv_sec = 3;
	timeout.it_value.tv_usec = 0;
	timeout.it_interval.tv_sec = 0;
	timeout.it_interval.tv_usec = 0;

	if (setitimer(ITIMER_REAL, &timeout, nullptr) < 0)
	{
		DebugLog(LogLevel::ERROR, "setitimer failed: %s", strerror(errno));
		FreeArgumentsArray(argv, argument_count);
		exit(ErrorCode::CORE_TIME_OUT);
	}

	// 执行核心程序
	execvp(("./" + core_executable_path).c_str(), argv);

	// 如果execvp返回，说明执行失败
	DebugLog(LogLevel::ERROR, "execvp failed: %s", strerror(errno));
	FreeArgumentsArray(argv, argument_count);
	exit(ErrorCode::CORE_EXECUTION_FAILED);
}

ErrorCode CoreCaller::WaitForChildProcess(pid_t pid, char **argv, size_t argument_count)
{
	int status;

	// 阻塞等待子进程结束
	waitpid(pid, &status, 0);

	// 释放参数数组内存
	FreeArgumentsArray(argv, argument_count);

	// 处理子进程退出状态
	return ProcessChildExitStatus(status);
}

ErrorCode CoreCaller::ProcessChildExitStatus(int status)
{
	// 处理超时（SIGALRM信号）
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
	{
		return ErrorCode::CORE_TIME_OUT;
	}

	// 处理正常退出
	if (WIFEXITED(status))
	{
		return ErrorCode(WEXITSTATUS(status));
	}

	// 处理信号终止
	if (WIFSIGNALED(status))
	{
		return ErrorCode::CORE_EXECUTION_FAILED;
	}

	// 其他情况
	return ErrorCode::CORE_EXECUTION_FAILED;
}