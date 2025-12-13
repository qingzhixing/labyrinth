#include <argument_parser.h>
#include <core_info.h>
#include <argument_validator.h>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Create argument parser instance
	ArgumentParser parser;

	// Parse the arguments
	auto [parsed_result, parse_error_code] = parser.ParseArguments(argc, argv);

	// 如果是帮助或版本请求，直接退出
	if (
		parse_error_code == GameCoreErrorCode::HELP_REQUESTED ||
		parse_error_code == GameCoreErrorCode::VERSION_REQUESTED)
	{
		return GameCoreErrorCode::SUCCESS;
	}

	// Check for parsing errors
	if (parse_error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, parse_error_code.toMessage());
		return parse_error_code.toInt();
	}

	// Validate the parsed result
	auto [validated_context, validate_error_code] = ValidateParsedResult(parsed_result);
	if (validate_error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, validate_error_code.toMessage());
		return validate_error_code.toInt();
	}

	return 0;
}