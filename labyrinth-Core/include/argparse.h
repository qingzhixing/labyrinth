#pragma once
#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <getopt.h>
#include <string>
#include <core_info.h>
#include <core_error_code.h>

struct ParsedResult
{
	std::string map_file{};
	std::string player_id{};
	std::string move_direction{};
};

typedef std::pair<ParsedResult, GameCoreErrorCode> ParsedResultWithErrorCode;

/**
 * @brief Print the version information of the program.
 *
 */
void PrintVersion();

/**
 * @brief Print the usage message of the program.
 *
 * labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [-v|--version]
 */
void PrintUsage();

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
 * @brief Validate the parsed result.
 *
 * @param parsedResult The parsed result.
 * @return GameCoreErrorCode The error code of the validation.
 */
GameCoreErrorCode ValidateParsedResult(const ParsedResult &parsedResult);

#endif // ARGPARSE_H
