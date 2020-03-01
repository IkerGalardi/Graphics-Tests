workspace "gltests"
    architecture "x64"
    startproject "gltests"

    configurations { "Debug", "Release" }

    flags = { "MultiProcessorCompile" }

    project "gltests"
        location "gltests"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir("bin")
        objdir("bin/obj")

        files 
        {
            "src/**.hh",
            "src/**.cc",
            "src/**.c",
            "src,**.h"
        }

        includedirs
        {
            "src"
        }

        links 
        {
            "SDL2",
            "GLEW",
            "GL",
            "X11",
            "SOIL"
        }

        filter "configurations:Debug"
            defines { CONFIG_DEBUG }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines { CONFIG_RELEASE }
            runtime "Release"
            optimize "on"