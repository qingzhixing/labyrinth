#pragma once
#ifndef GAME_CORE_INFO_H
#define GAME_CORE_INFO_H

#include <game_info.h>
#include <string>
#include <iostream>

inline const std::string PROGRAM_NAME = "labyrinth-Core";

inline void PrintVersion()
{
	std::cout << GAME_NAME_ASCII_ART << std::endl;
	std::cout << GAME_NAME << " " << GAME_VERSION << std::endl;
	std::cout << GAME_DESCRIPTION << std::endl;
	std::cout << "Author: " << AUTHOR << " (" << AUTHOR_EMAIL << ")" << std::endl;
}

inline void PrintUsage()
{
	std::cout
		<< "Usage: "
		<< PROGRAM_NAME
		<< " [-m|--map FILE] [--move DIRECTION] [-v|--version]"
		<< std::endl;

	std::cout << "Options:" << std::endl;
	std::cout
		<< "  -m, --map FILE    Specify the map file to use"
		<< std::endl;

	std::cout
		<< "      --move DIRECTION (up, down, left, right)    "
		<< "Specify the direction to move"
		<< std::endl;

	std::cout
		<< "  -v, --version    Show the version information"
		<< std::endl;

	std::cout
		<< "  -h, --help    Show this help message"
		<< std::endl;

	std::cout << "Tips:" << std::endl;
	std::cout << "  1. '--move' '-m' must be used together" << std::endl;
}

#endif // GAME_CORE_INFO_H