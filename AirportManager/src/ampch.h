#pragma once

#include <array>
#include <chrono>
#include <format>
#include <functional>
#include <iostream>

#ifdef AM_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN // Avoid extras
	#define NOMINMAX // Nobody wants this
	#include <Windows.h>
#endif
