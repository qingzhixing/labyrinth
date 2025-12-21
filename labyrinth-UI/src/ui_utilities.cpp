#include <ui_utilities.h>
#include <iostream>

void ClearScreen()
{
	// 清除屏幕
	std::cout << "\033[2J\033[1;1H";
}