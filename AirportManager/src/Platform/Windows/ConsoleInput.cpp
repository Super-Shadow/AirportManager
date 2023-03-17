#include "ampch.h"
#include "ConsoleInput.h"

std::string ConsoleInput::GetSingleWord()
{
	std::string str;
	std::cin >> str;
	return str;
}
