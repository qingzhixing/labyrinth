#include <testkit.h>
#include <types/core_error_code.h>

SystemTest(
	Labyrinth_Core_Help,
	((const char *[]){"--help"}))
{
	assert(
		result->exit_status ==
		GameCoreErrorCode::HELP_REQUESTED);
}

SystemTest(
	Labyrinth_Core_Help_Short,
	((const char *[]){"-h"}))
{
	assert(
		result->exit_status ==
		GameCoreErrorCode::HELP_REQUESTED);
}

SystemTest(
	Labyrinth_Core_Version,
	((const char *[]){"--version"}))
{
	assert(
		result->exit_status ==
		GameCoreErrorCode::VERSION_REQUESTED);
}

SystemTest(
	Labyrinth_Core_Version_Short,
	((const char *[]){"-v"}))
{
	assert(
		result->exit_status ==
		GameCoreErrorCode::VERSION_REQUESTED);
}