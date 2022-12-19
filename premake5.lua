
workspace "BlackbirdStealth"
	platforms { "x64" }
	configurations { "Debug", "Release", "Dist" }

	startproject "BlackbirdStealth"

	flags "MultiProcessorCompile"


include "Premake/PremakeUtilities/Utilities.lua"

-- Include directories relative to WKS
Solution.Name  = "BlackbirdStealth"
Solution.Projects["EngineCore"] 		= "%{wks.location}/EngineCore/"
Solution.Projects["Blackbird"] 			= "%{wks.location}/Blackbird/"
Solution.Projects["BlackbirdStealth"] 	= "%{wks.location}/BlackbirdStealth/"

include "EngineCore"
include "Blackbird"
include "BlackbirdStealth"

filter "action:vs*"
	Solution.CleanVSfiles()
	