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
            "%{prj.location}/*.h",
            "%{prj.location}/*.cpp"
        }

		includedirs
		{
			"%{prj.location}"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "Off"
			systemversion "latest"

			libdirs 
			{
				"%{prj.location}/Dependencies"
			}


		filter "configurations:Debug"
      		defines { "DEBUG" }
      		symbols "On"

   		filter "configurations:Release"
      		defines { "NDEBUG" }
      		optimize "On"
