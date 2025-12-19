#include "environment.h"
#include <cstdlib>

bool IsTestEnvironment()
{
	if (std::getenv("TK_RUN") != nullptr ||
		std::getenv("TK_VERBOSE") != nullptr)
	{
		return true;
	}
	return false;
}