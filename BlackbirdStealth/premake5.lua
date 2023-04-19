
Solution.ProjectsInfo.ProjectDependencies["BlackbirdStealth"] = {
	"ProjectCore",
	"LittleECS",
	"Blackbird"
}

project "BlackbirdStealth"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
    objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}
	
	includedirs {
		"src/"
	}

	Solution.Project("BlackbirdStealth")
