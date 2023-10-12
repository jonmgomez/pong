#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class VBO
{
public:
    GLuint id;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
