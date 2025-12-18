target("common")
	-- Set the target type to static library
	set_kind("static")
	set_languages("c++23")
	add_deps("debug_utils")

	-- Add the source files
	add_files("./src/*.cpp")
	
	-- Add the include directories
	add_includedirs("./include",{public = true})

target("common-test")
	set_kind("binary")
	set_languages("c++23")
	add_deps("debug_utils")
	add_deps("common", "testkit")
	add_files("./test/*.cpp")