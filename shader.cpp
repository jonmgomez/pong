#pragma once

#include "shader.h"

#include <string>
#include <fstream>


std::string getFileContents(const char *filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (file)
    {
        std::string contents;
        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        file.close();
        return contents;
    }
    throw(errno);
}

Shader::Shader(const GLchar* vertexFilePath, const GLchar* fragmentFilePath)
{
    std::string vertexCode = getFileContents(vertexFilePath);
    std::string fragmentCode = getFileContents(fragmentFilePath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(id);
}

void Shader::Delete()
{
    glDeleteProgram(id);
}
