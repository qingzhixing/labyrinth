#include <arg_parse.h>
#include <getopt.h>
#include <string>
#include <core_info.h>
#include <types/core_error_code.h>
#include <debug_log.h>
#include <vector>
#include <memory>
#include <cstring>
#include <core_info.h>

using std::string;

ParsedResultWithErrorCode ParseArguments(int argc, char *argv[])
{
	// 重置 optind 到 1，确保 getopt_long 从 argv[1] 开始解析
	optind = 1;

	struct option long_options[] = {
		{"map", required_argument, nullptr, 'm'},
		{"player", required_argument, nullptr, 'p'},
		{"move", required_argument, nullptr, 0},
		{"version", no_argument, nullptr, 'v'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, 0, nullptr, 0}};

	ParsedResult result{};
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;

	// 解析命令行参数
	int opt;
	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "m:p:vh", long_options, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'm':
			DebugLog(LogLevel::DEBUG, "map file: %s", optarg);
			result.map_file = optarg;
			break;
		case 'p':
			DebugLog(LogLevel::DEBUG, "player ID: %s", optarg);
			result.player_id = optarg;
			break;
		case 'v': // --version
			DebugLog(LogLevel::DEBUG, "version flag");

			// 判断是否有其他参数
			if (optind < argc)
			{
				DebugLog(LogLevel::ERROR, "excessive parameters when --version: %s", argv[optind]);
				error_code = GameCoreErrorCode::EXCESSIVE_PARAMETERS;
			}
			else
			{
				PrintVersion();
				error_code = GameCoreErrorCode::SUCCESS;
			}
			return std::make_pair(result, error_code);
			break;
		case 0:
			if (long_index == 2) // --move
			{
				result.move_direction = optarg;
			}
			break;
		case 'h': // --help
			PrintUsage();
			error_code = GameCoreErrorCode::HELP_REQUESTED;
			return std::make_pair(result, error_code);

			break;
		case '?': // other invalid options
			if (optopt == 'm' || optopt == 'p')
			{
				error_code = GameCoreErrorCode::MISSING_PARAMETERS;
			}
			else
			{
				error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			}
			return std::make_pair(result, error_code);
			break;
		default:
			error_code = GameCoreErrorCode::INVALID_PARAMETERS;
			return std::make_pair(result, error_code);

			break;
		}
	}

	// 检查参数是否合法
	error_code = GameCoreErrorCode::SUCCESS;
	return std::make_pair(result, error_code);
}
