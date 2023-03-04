
workspace "BlackbirdStealth"
	platforms { "x64" }
	configurations { "Debug", "Release", "Dist" }

	startproject "BlackbirdStealth"

	flags "MultiProcessorCompile"


include "PremakeUtilities/Utilities.lua"

-- Include directories relative to WKS
Solution.Name  = "BlackbirdStealth"
Solution.Projects["EngineCore"] 		= "%{wks.location}/EngineCore/"
Solution.Projects["Blackbird"] 			= "%{wks.location}/Blackbird/"
Solution.Projects["BlackbirdStealth"] 	= "%{wks.location}/BlackbirdStealth/"
Solution.Projects[""] 	= "%{wks.location}/BlackbirdSandbox/"

include "EngineCore"
include "Blackbird"
include "BlackbirdStealth"
include "BlackbirdSandbox"

filter "action:vs*"
	Solution.CleanVSfiles()
	