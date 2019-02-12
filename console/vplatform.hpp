#pragma once
#if __cplusplus < 201103L
#error 请添加[-std=c++11]编译参数。
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
#undef _LINUX_
#define _LINUX_	1
#endif
#if defined(WIN32) || defined(_WIN32)
#undef _WIN32_
#define _WIN32_	1
#endif
#if defined(ANDROID) || defined(__ANDROID__)
#undef _ANDROID_
#define _ANDROID_	1
#endif
