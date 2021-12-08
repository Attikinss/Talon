workspace "Talon"
    architecture "x64"
    startproject "Editor"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLAD"] = "Engine/Vendor/GLAD/include"
IncludeDirs["GLFW"] = "Engine/Vendor/GLFW/include"
IncludeDirs["SpdLog"] = "Engine/Vendor/SpdLog/include"

include "Engine/Vendor/GLAD"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/Source",
        "%{IncludeDirs.GLAD}",
        "%{IncludeDirs.GLFW}",
		"%{IncludeDirs.SpdLog}",
    }

    libdirs
    {
        "%{prj.name}/Vendor/GLFW/lib",
    }

    links
    {
        "GLAD",
        "glfw3_mt.lib",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "TALON_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TALON_RELEASE"
        runtime "Release"
        optimize "on"

project "Editor"
    location "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs
    {
		"%{prj.name}/Source",
        "Engine/Source",
		"%{IncludeDirs.SpdLog}",
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "TALON_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TALON_RELEASE"
        runtime "Release"
        optimize "on"