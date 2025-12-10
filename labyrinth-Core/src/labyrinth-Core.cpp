#include <arg_parse.h>
#include <debug_log.h>
#include <arg_validate.h>

int main(int argc, char *argv[])
{
	// Parse the arguments
	auto [parsed_result, parse_error_code] = ParseArguments(argc, argv);
	if (parse_error_code == GameCoreErrorCode::DEFAULT_ERROR_CODE ||
		(parse_error_code != GameCoreErrorCode::SUCCESS &&
		 parse_error_code != GameCoreErrorCode::HELP_REQUESTED))
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