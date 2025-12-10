#include <argparse.h>
#include <debug_log.h>

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
	return 0;
}