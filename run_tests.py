#!/usr/bin/env python3
import os
import subprocess
import sys
import argparse


def main():
    # 解析命令行参数
    parser = argparse.ArgumentParser(description="运行测试")
    parser.add_argument("-v", "--verbose", action="store_true", help="启用详细输出模式")
    args = parser.parse_args()

    # 构建项目
    if subprocess.run("xmake f -m debug && xmake", shell=True).returncode != 0:
        print("构建失败")
        sys.exit(1)

    # 设置环境变量
    env = os.environ.copy()
    if args.verbose:
        env["TK_VERBOSE"] = "1"
        print("启用详细输出模式 (TK_VERBOSE=1)")
    else:
        env["TK_RUN"] = "1"
        print("启用普通输出模式 (TK_RUN=1)")

    # 运行测试
    print("运行测试...")
    subprocess.run(["./build/labyrinth-Core"], env=env)
    subprocess.run(["./build/labyrinth-UI"], env=env)


if __name__ == "__main__":
    main()
