#!/bin/bash
xmake

# 运行所有测试
printf "=== Running labyrinth-Core tests ===\n"
TK_VERBOSE=1 ./build/labyrinth-Core

printf "\n=== Running labyrinth-UI tests ===\n"
TK_VERBOSE=1 ./build/labyrinth-UI
