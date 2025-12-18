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
	 * @brief Handle the map file option and return the updated result.
	 *
	 * @param result The current parsed result.
	 * @param optarg The option argument.
	 * @return ParsedResult The updated parsed result.
	 */
	ParsedResult HandleMapOption(const ParsedResult &result, const char *optarg);

	/**
	 * @brief Handle the version option.
	 *
	 * @param argc The number of arguments.
	 * @param argv The argument vector.
	 * @return ErrorCode The error code for version requested.
	 */
	ErrorCode HandleVersionOption(int argc, char *argv[]);

	/**
	 * @brief Handle the move option and return the updated result.
	 *
	 * @param result The current parsed result.
	 * @param optarg The option argument.
	 * @return ParsedResult The updated parsed result.
	 */
	ParsedResult HandleMoveOption(const ParsedResult &result, const char *optarg);

	/**
	 * @brief Handle the help option.
	 *
	 * @return ErrorCode The error code for help requested.
	 */
	ErrorCode HandleHelpOption();

	/**
	 * @brief Handle invalid options.
	 *
	 * @param optopt The option character that caused the error.
	 * @return GameCoreErrorCode The error code for invalid option.
	 */
	ErrorCode HandleInvalidOption(int optopt);

	// 声明测试类为友元类，以便测试私有函数
	friend class ArgumentParserTest;
};

#endif // ARGUMENT_PARSER_H