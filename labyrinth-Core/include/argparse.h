#pragma once
#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <getopt.h>
#include <string>
#include <core_info.h>
#include <core_error_code.h>

using std::string;
struct ParsedResult
{
	string map_file{};
	int player_id{};
	string move_direction{};
	GameCoreErrorCode error_code = GameCoreErrorCode::DEFAULT_ERROR_CODE;
};

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
 * @return ParsedResult The parsed arguments.
 */
ParsedResult ParseArguments(int argc, char *argv[]);

#endif // ARGPARSE_H
