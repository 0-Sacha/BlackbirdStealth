
workspace "Sandbox"
	platforms { "x64" }
	configurations { "Debug", "Release", "Dist" }

	startproject "Sandbox"

	flags "MultiProcessorCompile"


include "Premake/PremakeUtilities/Utilities.lua"

-- Include directories relative to WKS
Solution.Name  = "Sandbox"
Solution.Projects["EngineCore"] 	= "%{wks.location}/EngineCore/"
Solution.Projects["Blackbird"] 		= "%{wks.location}/Blackbird/"
Solution.Projects["Sandbox"] 		= "%{wks.location}/Sandbox/"

include "EngineCore"
include "Blackbird"
include "Sandbox"

filter "action:vs*"
	Solution.CleanVSfiles()
	