#include "ampch.h"
// Precompiled header file (PCH) must be included at top of all source files.
// The main benefit to using a PCH is that when files need to be recompiled (usually due to code changes),
// the PCH does not need to be recompiled. This speeds up build times as long as headers inside the PCH
// do not need to be recompiled frequently as all files that use the PCH will need to be recompiled.

#include "Application.h"

// Entry point for C++ applications is different on each platform (windows, macos and linux),
// so provide a platform specific implementation of the entry point.
// This allows for this program to be developed in the future for different platforms
// The definition of the platform is generated automatically by the build configuration such as CMake or Premake.
#ifdef AM_PLATFORM_WINDOWS

int main()
{
	// Handle any exceptions that might be thrown during runtime,
	// since if they are thrown and not handled the program might leak memory
	// due to destructors of existing objects not being called.
	// For more info check this out -> https://stackoverflow.com/questions/368184/does-it-make-sense-to-catch-exceptions-in-the-main
	try
	{
		const auto app = new Application();
		app->Run();
		delete app;
	}
	catch(std::exception& e)
	{
		// Should ideally write this out to a crash file but this will work for now!
		std::cout << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#endif