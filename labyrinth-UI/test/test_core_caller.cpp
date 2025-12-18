#include <core_caller.h>
#include <testkit.h>
#include <debug_log.h>
#include <filesystem>
#include <format>
#include <fstream>

using std::format;
using std::string;

UnitTest(CoreCallerValidateCoreExecutable_Valid)
{
	DebugLog(
		LogLevel::INFO,
		format("Validating core executable: {}", GAME_CORE_EXECUTABLE_NAME));

	// 打印当前目录
	DebugLog(
		LogLevel::INFO,
		format("Current directory: {}", std::filesystem::current_path().string()));

	assert(CoreCaller::ValidateCoreExecutable(GAME_CORE_EXECUTABLE_NAME));
}

UnitTest(CoreCallerValidateCoreExecutable_MissingFile)
{
	auto missing_file_path =
		"Missing_File_" + std::to_string(rand());

	DebugLog(
		LogLevel::INFO,
		format("Validating core executable: {}", missing_file_path));

	assert(!CoreCaller::ValidateCoreExecutable(missing_file_path));
}

UnitTest(CoreCallerValidateCoreExecutable_FileIsDirectory)
{
	auto directory_path =
		"Directory_" + std::to_string(rand());

	std::filesystem::create_directory(directory_path);

	DebugLog(
		LogLevel::INFO,
		format("Validating core executable: {}", directory_path));

	auto result = CoreCaller::ValidateCoreExecutable(directory_path);

	std::filesystem::remove(directory_path);

	assert(!result);
}

UnitTest(CoreCallerValidateCoreExecutable_FileIsNotExecutable)
{
	auto non_executable_file_path =
		"Non_Executable_File_" + std::to_string(rand());

	std::ofstream non_executable_file(non_executable_file_path);

	non_executable_file.close();

	DebugLog(
		LogLevel::INFO,
		format("Validating core executable: {}", non_executable_file_path));

	auto result = CoreCaller::ValidateCoreExecutable(non_executable_file_path);

	std::filesystem::remove(non_executable_file_path);

	assert(!result);
}