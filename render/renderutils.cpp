#include "renderutils.h"

#include <GL/glew.h>

#include <spdlog/spdlog.h>

namespace pong
{

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        spdlog::error("[OpenGL Error] ({}) {} {}:{}", error, function, file, line);
        return false;
    }
    return true;
}

} // namespace pong
