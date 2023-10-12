#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

std::string getFileContents(const char *filePath);

class Shader
{
public:
    GLuint id;
    Shader(const GLchar* vertexFilePath, const GLchar* fragmentFilePath);

    void Activate();
    void Delete();
};
