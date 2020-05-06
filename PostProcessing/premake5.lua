workspace "PostProcessing"
    architecture "x64"
    startproject "PostProcessing"

    configurations { "Debug", "Release" }

    flags = { "MultiProcessorCompile" }

    project "PostProcessing"
        location "PostProcessing"
        kind "ConsoleApp"
        language "C"
        cdialect "C11"
        staticruntime "on"

        targetdir("bin")
        objdir("bin/obj")

        files 
        {
            "PostProcessing/**.c",
            "PostProcessing/src/**.h"
        }

        includedirs
        {
            "PostProcessing/src",
            "PostProcessing/external"
        }

        links 
        {
            "SDL2",
            "GLEW",
            "GL", 
            "m"
        }

        filter "configurations:Debug"
            defines { CONFIG_DEBUG }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines { CONFIG_RELEASE }
            runtime "Release"
            optimize "on"