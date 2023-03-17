#include "ampch.h"
#include "Input.h"

// See EntryPoint for why this is done.
#ifdef AM_PLATFORM_WINDOWS
#include "Platform/Windows/ConsoleInput.h"
#endif

Input* Input::Create()
{
	#ifdef AM_PLATFORM_WINDOWS
	return new ConsoleInput();
	#else
	throw std::exception("No platform implementation for Input!");
	#endif
}
