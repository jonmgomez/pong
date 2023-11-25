#pragma once

#include <spdlog/spdlog.h>

#include <iostream>

namespace pong
{

#ifdef DEBUG
    #define ASSERT(x) if (!(x)) \
    { \
        std::cout << "Assertion failed: (" << #x << "), File: " __FILE__  ", Line: " << __LINE__ << std::endl; \
        __debugbreak(); \
    }
#else
    #define ASSERT(cond) \
        do { (void)sizeof(cond); } while(0)
#endif

#ifdef DEBUG
    #define MEASURE_TIME(x, name) \
    { \
        const auto start = std::chrono::high_resolution_clock::now(); \
        x; \
        const auto end = std::chrono::high_resolution_clock::now(); \
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); \
        std::cout << name << ", Time taken: " << duration.count() << "us" << std::endl; \
    }
#else
    #define MEASURE_TIME(x, name) \
        do { (void)sizeof(x); } while(0)
#endif

}

