#!/usr/bin/env python3
import os
import subprocess
import sys
import argparse


def main():
    # 解析命令行参数
    parser = argparse.ArgumentParser(description="运行测试")
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="启用 Debug 日志输出"
    )
    args = parser.parse_args()

    # 构建项目
    if subprocess.run("xmake f -m debug && xmake", shell=True).returncode != 0:
        print("构建失败")
        sys.exit(1)

    # 设置环境变量
    env = os.environ.copy()
    env["TK_VERBOSE"] = "1"
    if args.verbose:
        print("启用 Debug 日志输出 (DBG_LOG_ENABLE=1)")
        env["DBG_LOG_ENABLE"] = "1"
    else:
        print("启用普通输出模式 (Undefined DBG_LOG_ENABLE)")

    # 运行测试,运行目录: ./build
    print("运行测试...")
    # 运行 common-test
    subprocess.run(["./common-test"], env=env, cwd="./build", check=False)
    # 运行 labyrinth-Core
    print("运行 labyrinth-Core...")
    subprocess.run(["./labyrinth-Core"], env=env, cwd="./build", check=False)
    # 运行 labyrinth-UI
    print("运行 labyrinth-UI...")
    subprocess.run(["./labyrinth-UI"], env=env, cwd="./build", check=False)


if __name__ == "__main__":
    main()
