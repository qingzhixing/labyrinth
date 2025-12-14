#pragma once
#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <argument_result.h>

// 前向声明测试友元类
class ArgumentParserTest;

/**
 * @brief Argument parser class for parsing command line arguments.
 */
class ArgumentParser
{
public:
	/**
	 * @brief Default constructor.
	 */
	ArgumentParser() = default;

	/**
	 * @brief Parse the command line arguments.
	 *
	 * @param argc The number of command line arguments.
	 * @param argv The command line arguments.
	 *
	 * @return ParsedResultWithErrorCode The parsed arguments with error code.
	 *
	 * The error code is describing only the result of the parsing.
	 */
	ParsedResultWithErrorCode ParseArguments(int argc, char *argv[]);

	/**
	 * @brief Print the version information of the program.
	 */
	static void PrintVersion();

	/**
	 * @brief Print the usage message of the program.
	 *
	 * labyrinth [-m|--map FILE] [--move DIRECTION] [-v|--version]
	 */
	static void PrintUsage();

private:
	/**
	 * @brief Reset the getopt state to ensure proper parsing.
	 */
	void ResetGetoptState();

	/**
	 * @brief Handle the map file option.
	 *
	 * @param result The parsed result to update.
	 * @param optarg The option argument.
	 */
	void HandleMapOption(ParsedResult &result, const char *optarg);

	/**
	 * @brief Handle the version option.
	 *
	 * @param argc The number of arguments.
	 * @param argv The argument vector.
	 * @param error_code The error code to set.
	 * @return bool True if processing should stop, false otherwise.
	 */
	bool HandleVersionOption(int argc, char *argv[], GameCoreErrorCode &error_code);

	/**
	 * @brief Handle the move option.
	 *
	 * @param result The parsed result to update.
	 * @param optarg The option argument.
	 */
	void HandleMoveOption(ParsedResult &result, const char *optarg);

	/**
	 * @brief Handle the help option.
	 *
	 * @param error_code The error code to set.
	 * @return bool True if processing should stop, false otherwise.
	 */
	bool HandleHelpOption(GameCoreErrorCode &error_code);

	/**
	 * @brief Handle invalid options.
	 *
	 * @param optopt The option character that caused the error.
	 * @param error_code The error code to set.
	 * @return bool True if processing should stop, false otherwise.
	 */
	GameCoreErrorCode HandleInvalidOption(int optopt);

	// 声明测试类为友元类，以便测试私有函数
	friend class ArgumentParserTest;
};

#endif // ARGPARSE_H