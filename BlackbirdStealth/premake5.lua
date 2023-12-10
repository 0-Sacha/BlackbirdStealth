
Solution.Projects["BlackbirdStealth"].ProjectDependencies = {
	"ProjectCore",
	"LittleECS",
	"Blackbird"
}

project "BlackbirdStealth"
	kind 		(Solution.Projects["BlackbirdStealth"].Type)
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

	Solution.Project("BlackbirdStealth")
