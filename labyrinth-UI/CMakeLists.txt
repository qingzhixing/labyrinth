cmake_minimum_required(VERSION 3.10)
project(labyrinth-UI VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ggdb -Wall")

# 如果将来有UI相关的源文件，可以在这里添加
# 例如：add_executable(labyrinth-UI ui-source.cpp)

message(STATUS "labyrinth-UI模块已配置，但当前没有源文件需要构建")