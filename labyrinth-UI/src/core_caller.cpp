#include <core_caller.h>
#include <filesystem>

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
	// TODO: Call core executable
	return ErrorCode::SUCCESS;
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
