#include "renderutils.h"

#include "logger.h"

#include <GL/glew.h>

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
        LogError("[OpenGL Error] ({}) {} {}:{}", error, function, file, line);
        return false;
    }
    return true;
}

} // namespace pong
