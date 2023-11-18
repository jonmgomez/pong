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

}

