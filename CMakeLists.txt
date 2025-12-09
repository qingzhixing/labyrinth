cmake_minimum_required(VERSION 3.10)
project(labyrinth VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ggdb -Wall")

# 添加子目录
add_subdirectory(labyrinth-Core)
add_subdirectory(labyrinth-UI)
