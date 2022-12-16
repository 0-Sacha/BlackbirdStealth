
Solution.Path = {}
Solution.Path.OutputDirectory = Solution.System .. "-" .. Solution.Premake.Mode .. "/%{cfg.buildcfg}-%{cfg.platform}"

Solution.Path.TargetDirectory = "%{wks.location}/bin/" .. Solution.Path.OutputDirectory
Solution.Path.ObjectDirectory = "%{wks.location}/bin-int/" .. Solution.Path.OutputDirectory

Solution.Path.ProjectTargetDirectory = Solution.Path.TargetDirectory .. "/%{prj.name}"
Solution.Path.ProjectObjectDirectory = Solution.Path.ObjectDirectory .. "/%{prj.name}"
