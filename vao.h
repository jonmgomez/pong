#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "vbo.h"

class VAO
{
public:
    GLuint id;
    VAO();

    void LinkVBO(VBO vbo, int layout);
    void Bind();
    void Unbind();
    void Delete();
};
