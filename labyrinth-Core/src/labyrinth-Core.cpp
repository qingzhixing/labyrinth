#include <arg_parse.h>
#include <debug_log.h>
#include <arg_validate.h>

int main(int argc, char *argv[])
{
	auto [parsed_result, error_code] = ParseArguments(argc, argv);
	if (error_code == GameCoreErrorCode::DEFAULT_ERROR_CODE ||
		(error_code != GameCoreErrorCode::SUCCESS &&
		 error_code != GameCoreErrorCode::HELP_REQUESTED))
	{
		DebugLog(LogLevel::ERROR, error_code.toMessage());
		return error_code.toInt();
	}

	error_code = ValidateParsedResult(parsed_result);
	if (error_code != GameCoreErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, error_code.toMessage());
		return error_code.toInt();
	}

	return 0;
}