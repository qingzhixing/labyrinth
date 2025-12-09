cmake_minimum_required(VERSION 3.10)
project(labyrinth-Core VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ggdb -Wall")

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/../testkit)

# 源文件
set(SOURCES
    labyrinth-Core.cpp
    ${CMAKE_SOURCE_DIR}/../testkit/testkit.c
)

# 创建可执行文件
add_executable(labyrinth-Core ${SOURCES})

