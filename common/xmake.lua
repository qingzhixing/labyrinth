target("common")
	-- Set the target type to static library
	set_kind("static")

	-- Add the source files
	add_files("./src/*.cpp")
	
	-- Add the include directories
	add_includedirs("./include",{public = true})
