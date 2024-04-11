---@diagnostic disable: undefined-global, undefined-field
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

-- Clean Function --
newaction {
   trigger     = "clean",
   description = "clean the software",
   execute     = function ()
      print("clean the bin...")
      os.rmdir("./bin")
      print("clean the build...")
      os.rmdir("./build")
      print("clean the Makefile...")
      os.remove("./Makefile")
      print("done.")
   end
}
