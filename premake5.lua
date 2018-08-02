
workspace "filehawk"
    if _ACTION then
        location( "build/" .. _ACTION )
    end
    configurations { "Debug", "Release" }
    
    project "filehawk"
        kind "StaticLib"
        language "C++"
        targetdir "lib/"
        
        files { "source/**.cpp" }
        includedirs { "include/" }
        
        filter "configurations:Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
            
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
            
        filter "action:gmake"
            buildoptions { "-std=gnu++11" }
            
    project "demo"
        kind "ConsoleApp"
        language "C++"
        targetdir("bin/")
        files {
            "source/*.cpp",
            "SimpleDemo.cpp"
        }
        includedirs( "include" )
        
        filter "configurations:Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
            
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        
        filter "action:gmake"
            buildoptions { "-std=gnu++11" }
            