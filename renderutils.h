#pragma once

#include <GL/glew.h>

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
    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#else
    #define GLCall(x) x
#endif

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

} // namespace pong
