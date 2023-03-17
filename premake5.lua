workspace "AirportManager"
	architecture "x86_64"
	startproject "AirportManager" 

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile",
		"FatalWarnings"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}

group ""

project "AirportManager"
	location "AirportManager"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	vectorextensions "AVX2"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ampch.h"
	pchsource "AirportManager/src/ampch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}
	
	filter "system:windows"
		systemversion "latest"
		warnings "high"
		defines "AM_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "Full"

	filter "configurations:Release"
		defines "AM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AM_DIST"
		runtime "Release"
		symbols "Off"
		optimize "on"