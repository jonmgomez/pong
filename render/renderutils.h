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

struct RGBAColor
{
    unsigned char r {0};
    unsigned char g {0};
    unsigned char b {0};
    unsigned char a {0};
};

// Separate RGBAColor struct to avoid converting to opengl's 0.0f - 1.0f range too often
struct GLRGBAColor
{
    float r { 1.0f };
    float g { 1.0f };
    float b { 1.0f };
    float a { 1.0f };

    GLRGBAColor() = default;

    GLRGBAColor(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a)
    {
    }

    GLRGBAColor(const RGBAColor& color) :
        r(color.r / 255.0f), g(color.g / 255.0f),
        b(color.b / 255.0f), a(color.a / 255.0f)
    {
    }
};

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

} // namespace pong
