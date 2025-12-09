#include <iostream>
#include <testkit.h>
#include <debug_run.h>

int main(int argc, char *argv[])
{
	std::cout << "labyrinth-UI" << std::endl;
	DebugRun({
		std::cout << "Hello, Testkit!" << std::endl;
		std::cout << "Debug information" << std::endl;
	});
	return 0;
}