-- I Would like to say: Fuck you,CMake!

set_targetdir("./build")

-- 添加编译模式配置
add_rules("mode.debug", "mode.release")

-- 设置debug模式的编译选项
if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
    add_cxflags("-ggdb", "-O0")
    add_mxflags("-ggdb", "-O0")
end

-- 设置release模式的编译选项
if is_mode("release") then
    set_symbols("hidden")
    set_optimize("fastest")
    set_strip("all")
    add_cxflags("-O2", "-DNDEBUG")
    add_mxflags("-O2", "-DNDEBUG")
end

-- 设置C++标准版本（推荐使用C++17）
set_languages("c++23")

-- Libs
includes("debug_utils")
includes("testkit")
includes("common")

-- Binaries
includes("labyrinth-Core")
includes("labyrinth-UI")