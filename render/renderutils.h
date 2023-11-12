#pragma once

#include "utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pong
{

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
