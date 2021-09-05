workspace "FlappyBirdClone"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    startproject "FlappyBirdClone"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FlappyBirdClone"
    location "FlappyBirdClone"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" ..outputdir.. "/%{prj.name}")
    objdir("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**.h",
        "%{prj.location}/res/**.png"
    }

    includedirs
    {
        "%{prj.location}/include",
        "%{wks.location}/Dependencies/SDL2/include",
        "%{wks.location}/Dependencies/SDL2_image/include"
    }

    defines
    {
        "WINDOWS"
    }

    links
    {
        "SDL2",
        "SDL2main",
        "SDL2_image"
    }

    libdirs
    {
        "%{wks.location}/Dependencies/SDL2/lib/x64",
        "%{wks.location}/Dependencies/SDL2_image/lib/x64"
    }

    filter {"configurations:Debug"}
        buildoptions "/MTd"
        runtime "Debug"
        symbols "on"

        postbuildcommands
        {
            "{COPYDIR} \"%{wks.location}/Dependencies/SDL2/lib/x64\" \"%{cfg.targetdir}\"",
            "{COPYDIR} \"%{wks.location}/Dependencies/SDL2_image/lib/x64\" \"%{cfg.targetdir}\""
        }

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"

        
newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}