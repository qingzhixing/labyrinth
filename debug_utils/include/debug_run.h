#pragma once
#ifndef DEBUG_RUN_H
#define DEBUG_RUN_H

#ifndef NDEBUG

// 方案1：使用更优雅的语法，支持多行代码
#define DebugRun(...) \
	do                \
	{                 \
		__VA_ARGS__;  \
	} while (0)

#else

#define DebugRun(...) ((void)0)

#endif // NDEBUG

#endif //! DEBUG_RUN_H