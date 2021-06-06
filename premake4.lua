runner_files = { gkit_dir .. "/runner/*.cpp", gkit_dir .. "/runner/*.hpp" }

project("runner")
	language "C++"
	kind "ConsoleApp"
	targetdir ( gkit_dir .. "/bin" )
	files ( gkit_files )
	files ( runner_files )
	files { gkit_dir .. "/runner/main.cpp" }