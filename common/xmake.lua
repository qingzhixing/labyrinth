target("common")
	-- Set the target type to static library
	set_kind("static")
	set_languages("c++17")
	add_deps("debug_utils")

	-- Add the source files
	add_files("./src/*.cpp")
	
	-- Add the include directories
	add_includedirs("./include",{public = true})

-- 添加独立的测试目标
target("common-test")
	set_kind("binary")
	set_languages("c++17")
	add_deps("debug_utils")
	add_deps("common", "testkit")  -- 测试目标依赖common和testkit
	add_files("./test/*.cpp")      -- 添加测试文件