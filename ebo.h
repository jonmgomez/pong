#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class EBO
{
public:
    GLuint id;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};