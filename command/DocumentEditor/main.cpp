#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>

int main()
{
	CUserInterface ui(std::cin, std::cout);
	ui.StartListeningInput();
}
