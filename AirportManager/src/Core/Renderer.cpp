#include "ampch.h"
#include "Renderer.h"

// See EntryPoint for why this is done.
#ifdef AM_PLATFORM_WINDOWS
#include "Platform/Windows/ConsoleRenderer.h"
#endif

Renderer* Renderer::Create(const Params&& params)
{
	#ifdef AM_PLATFORM_WINDOWS
	return new ConsoleRenderer(params);
	#else
	throw std::exception("No platform implementation for Renderer!");
	#endif
}
