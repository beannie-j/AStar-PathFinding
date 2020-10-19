workspace "AStar-PathFinding"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "AStar-PathFinding"
		location "."
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
        {
            "%{prj.location}/AStar/src/Logic/*.h",
            "%{prj.location}/AStar/src/Logic/*.cpp",
			"%{prj.location}/AStar/src/Graphics/*.cpp",
			"%{prj.location}/AStar/src/Graphics/*.h",
			"%{prj.location}/AStar/src/Graphics/Layers/*.cpp",
			"%{prj.location}/AStar/src/Graphics/Layers/*.h",
			"%{prj.location}/AStar/src/Application/*.cpp",
			"%{prj.location}/AStar/src/Application/*.h"
        }

		includedirs
		{
			"%{prj.location}",
			"%{prj.location}/Dependencies/include",
			"%{prj.location}/AStar/src/Logic",
			"%{prj.location}/AStar/src/Graphics",
			"%{prj.location}/AStar/src/Graphics/Layers",
			"%{prj.location}/AStar/src/Application"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "Off"
			systemversion "latest"

			defines
			{
				"SFML_STATIC"
			}

			libdirs 
			{
				"%{prj.location}/Dependencies/lib",
				"%{prj.location}/Dependencies/bin"
			}

			links { "openal32.lib","sfml-audio-s-d.lib","ogg.lib","vorbis.lib","vorbisfile.lib","vorbisenc.lib","flac.lib","sfml-main-d.lib","ws2_32.lib","gdi32.lib","winmm.lib","freetype.lib","opengl32.lib","sfml-network-s-d.lib","sfml-graphics-s-d.lib","sfml-window-s-d.lib","sfml-system-s-d.lib","kernel32.lib","user32.lib","gdi32.lib","winspool.lib","comdlg32.lib","advapi32.lib","shell32.lib","ole32.lib","oleaut32.lib","uuid.lib","odbc32.lib","odbccp32.lib" }


		filter "configurations:Debug"
      		defines { "DEBUG" }
      		symbols "On"

   		filter "configurations:Release"
      		defines { "NDEBUG" }
      		optimize "On"

		configuration "windows"
   		postbuildcommands { "copy %{prj.location}Dependencies\\bin\\openal32.dll %{prj.location}bin\\" .. outputdir .. "\\%{prj.name}" }