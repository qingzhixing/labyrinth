target("labyrinth-Core")
	set_kind("binary")
	set_languages("c++17")
	add_deps("testkit", "common", "debug_utils")

	-- Add include directories
	add_includedirs("./include", {public = true})

	-- Add source files
	add_files("./src/*.cpp")

	-- Add test files
	add_files("./test/*.cpp")