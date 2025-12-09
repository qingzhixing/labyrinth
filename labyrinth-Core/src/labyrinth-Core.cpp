#include <argparse.h>
#include <debug_log.h>

int main(int argc, char *argv[])
{
	auto result = ParseArguments(argc, argv);
	if (result.error_code == GameCoreErrorCode::DEFAULT_ERROR_CODE)
	{
		DebugLog(LogLevel::DEBUG, "default error code");
	}
	if (result.error_code != GameCoreErrorCode::SUCCESS &&
		result.error_code != GameCoreErrorCode::HELP_REQUESTED)
	{
		return result.error_code;
	}
	return 0;
}
