#pragma once
#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <arg_result.h>

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

#endif // ARGPARSE_H
