---@diagnostic disable: undefined-global
workspace "bf"
    configurations { "Release", "Debug" }
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

project "bf"
    kind "ConsoleApp"
    location "build"
    files { "src/*.c" }
    includedirs { "include", "src" }
    links { "List" }

    filter "configurations:Release"
        optimize "On"
        symbols "Off"

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"

project "List"
    kind "StaticLib"
    location "build"
    files { "src/List/src/*.c" }
    includedirs { "include", "src" }
