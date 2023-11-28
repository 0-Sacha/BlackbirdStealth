
Solution.ProjectsInfo.ProjectDependencies["BlackbirdLauncher"] = {
	"ProjectCore",
	"LittleECS",
	"Blackbird"
}

project "BlackbirdLauncher"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

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

	Solution.Project("BlackbirdLauncher")
	