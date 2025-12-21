#include <argument_parser.h>
#include <core_info.h>
#include <argument_validator.h>
#include <types/error_code.h>
#include <debug_log.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Create argument parser instance
	ArgumentParser parser;

	// Parse the arguments
	auto [parsed_result, parse_error_code] =
		parser.ParseArguments(argc, argv);

	// 如果是帮助或版本请求，直接退出
	if (parse_error_code == ErrorCode::HELP_REQUESTED ||
		parse_error_code == ErrorCode::VERSION_REQUESTED)
	{
		return ErrorCode::SUCCESS;
	}

	// Check for parsing errors
	if (parse_error_code != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, parse_error_code.toMessage());
		return parse_error_code.toInt();
	}

	// Validate the parsed result
	auto [validated_context, validate_error_code] = ValidateParsedResult(parsed_result);
	if (validate_error_code != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, validate_error_code.toMessage());
		return validate_error_code.toInt();
	}

	auto [game_map, map_file_path, move_direction, validate] = validated_context;

	// 如果是验证模式，直接退出
	if (validate)
	{
		return ErrorCode::SUCCESS;
	}

	// Move the player
	auto move_result = game_map.MovePlayer(move_direction);
	if (move_result != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, move_result.toMessage());
		return move_result.toInt();
	}

	// 写回地图
	auto write_back_result = game_map.WriteBackMap(map_file_path);
	if (write_back_result != ErrorCode::SUCCESS)
	{
		DebugLog(LogLevel::ERROR, write_back_result.toMessage());
		return write_back_result.toInt();
	}

	return 0;
}