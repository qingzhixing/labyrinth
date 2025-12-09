#!/usr/bin/env python3
import os
import subprocess
import sys

# 构建项目
if subprocess.run("xmake f -m debug && xmake", shell=True).returncode != 0:
    print("构建失败")
    sys.exit(1)


# 启用测试
env = os.environ.copy()
env["TK_VERBOSE"] = "1"

# 运行测试
subprocess.run(["./build/labyrinth-Core"], env=env)
subprocess.run(["./build/labyrinth-UI"], env=env)
