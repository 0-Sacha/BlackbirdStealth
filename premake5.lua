
workspace "BlackbirdStealth"
	platforms { "x64" }
	configurations { "Debug", "Release", "Dist" }

	startproject "BlackbirdStealth"

	flags "MultiProcessorCompile"


include "PremakeUtilities/Utilities.lua"

-- Include directories relative to WKS
Solution.Name  = "BlackbirdStealth"
Solution.AddProject("ProjectCore", 			"%{wks.location}/ProjectCore/")
Solution.AddProject("LittleECS", 			"%{wks.location}/LittleECS/")
Solution.AddProject("Blackbird", 			"%{wks.location}/Blackbird/")
Solution.AddProject("BlackbirdStealth", 	"%{wks.location}/BlackbirdStealth/")
Solution.AddProject("BlackbirdLauncher", 	"%{wks.location}/BlackbirdLauncher/")

include "ProjectCore"
include "LittleECS"
include "Blackbird"
include "BlackbirdStealth"
include "BlackbirdLauncher"
	