#include <iostream>
#include <testkit.h>

int main(int argc, char *argv[])
{
	std::cout << "labyrinth-UI" << std::endl;
	return 0;
}

void HelloTestkit()
{
	std::cout << "Hello, Testkit!" << std::endl;
}

UnitTest(HelloTestkit) {}