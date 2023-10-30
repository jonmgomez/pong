#include "main.h"

#include "input.h"
#include "pong.h"
#include "renderer.h"
#include "renderutils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

GLFWwindow* SetupGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit() failure" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "glfwCreateWindow() failure" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, Input::KeyCallback);

    // Uncomment this if you would like to blow up the GPU :D
    // glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glewInit() failure" << std::endl;
        return nullptr;
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    int numTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextureSlots);
    std::cout << "Texture Slots Available: " << numTextureSlots << std::endl;

    return window;
}

int main()
{
    std::cout << "Hello World!" << std::endl;

    GLFWwindow* window = SetupGLFW();
    if (window == nullptr)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, Input::KeyCallback);

    // Uncomment this if you would like to blow up the GPU :D
    // glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit() failure" << std::endl;
        return -1;
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    int numTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextureSlots);
    std::cout << "Texture Slots Available: " << numTextureSlots << std::endl;

    Renderer::SetShader("D:\\code\\pong\\basic.shader");

    // mark time
    double lastTime = glfwGetTime();
    int frameCount = 0;

    Pong pong;
    pong.PongInit();

    while (!glfwWindowShouldClose(window))
    {
        Renderer::Clear();

        pong.PongGameLoop();

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
