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
IncludeDirs["Assimp"] = "Engine/Vendor/Assimp/include"
IncludeDirs["ENTT"] = "Engine/Vendor/ENTT"
IncludeDirs["GLAD"] = "Engine/Vendor/GLAD/include"
IncludeDirs["GLFW"] = "Engine/Vendor/GLFW/include"
IncludeDirs["GLM"] = "Engine/Vendor/GLM"
IncludeDirs["ImGui"] = "Engine/Vendor/ImGui"
IncludeDirs["SpdLog"] = "Engine/Vendor/SpdLog/include"

include "Engine/Vendor/GLAD"
include "Engine/Vendor/ImGui"

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
        "%{IncludeDirs.Assimp}",
        "%{IncludeDirs.ENTT}",
        "%{IncludeDirs.GLAD}",
        "%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLM}",
        "%{IncludeDirs.ImGui}",
		"%{IncludeDirs.SpdLog}",
    }

    libdirs
    {
        "%{prj.name}/Vendor/Assimp/lib",
        "%{prj.name}/Vendor/GLFW/lib",
    }

    links
    {
        "GLAD",
        "ImGui",
        "glfw3_mt.lib",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "TALON_DEBUG"
        runtime "Debug"
        symbols "on"
        links
        {
            "assimp-vc142-mtd.lib",
            "IrrXMLd.lib",
            "zlibstaticd.lib"
        }

    filter "configurations:Release"
        defines "TALON_RELEASE"
        runtime "Release"
        optimize "on"
        links
        {
            "assimp-vc142-mt.lib",
            "IrrXML.lib",
            "zlibstatic.lib"
        }

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
        "%{IncludeDirs.ENTT}",
        "%{IncludeDirs.GLM}",
        "%{IncludeDirs.ImGui}",
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