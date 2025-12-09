#!/bin/bash

# 构建debug版本
xmake f -m debug
xmake

# 运行所有测试
echo "\n\n=== Running labyrinth-Core tests ==="
TK_VERBOSE=1 ./build/labyrinth-Core

echo "\n\n=== Running labyrinth-UI tests ==="
TK_VERBOSE=1 ./build/labyrinth-UI
