#include <core_caller.h>
#include <filesystem>

GameCoreErrorCode
CoreCaller::CallCoreExecutable(
	const std::string &core_executable_path,
	const std::vector<std::string> &arguments)
{
	// TODO: Unimplemented
	return GameCoreErrorCode::DEFAULT_ERROR_CODE;
}

bool CoreCaller::ValidateCoreExecutable(const std::string &core_executable_path)
{
	if (!std::filesystem::exists(core_executable_path))
	{
		return false;
	}

	if (!std::filesystem::is_regular_file(core_executable_path))
	{
		return false;
	}

	// Not executable
	if ((std::filesystem::status(core_executable_path).permissions() &
		 std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
	{
		return false;
	}

	return true;
}
