#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    if (!glfwInit())
    {
        std::cout << "glfwInit() failure" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "glfwCreateWindow() failure" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Uncomment this if you would like to blow up the GPU :D
    // glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit() failure" << std::endl;
        return -1;
    }

    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;

    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6);

    Shader shaderProgram = Shader("D:\\code\\pong\\basic.shader");
    shaderProgram.Bind();
    shaderProgram.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

    // mark time
    double lastTime = glfwGetTime();
    int frameCount = 0;

    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Bind();
        shaderProgram.SetUniform4f("u_Color", r, 0.0f, 1.0f, 1.0f);

        vb.Bind();
        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;
        frameCount++;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    double currentTime = glfwGetTime();
    double elapsedTime = currentTime - lastTime;

    std::cout << "Elapsed time: " << elapsedTime << std::endl;
    std::cout << "Total frames: " << frameCount << std::endl;
    std::cout << "Avg framerate: " << frameCount / elapsedTime << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
