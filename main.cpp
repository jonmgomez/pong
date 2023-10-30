#include "main.h"

#include "input.h"
#include "pong.h"
#include "renderer.h"
#include "renderutils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <string>

using namespace pong;

nlohmann::json OpenJsonFile(const std::string& filePath)
{
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open())
    {
        std::cerr << "Failed to open JSON file: " << filePath << std::endl;
        return nullptr;
    }

    nlohmann::json jsonData;

    try
    {
        jsonFile >> jsonData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return nullptr;
    }

    return jsonData;
}

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

void PlayPong(GLFWwindow* window)
{
    Pong pong;
    pong.PongInit();

    double lastTime = glfwGetTime();
    int frameCount = 0;

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

    Renderer::Cleanup();
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <json_file_path>" << std::endl;
        return -1;
    }

    nlohmann::json jsonData = OpenJsonFile(argv[1]);
    if (jsonData == nullptr)
    {
        return -1;
    }

    GLFWwindow* window = SetupGLFW();
    if (window == nullptr)
    {
        return -1;
    }

    if (jsonData.find("shader") == jsonData.end())
    {
        std::cerr << "Config file does not contain \"shader\" key." << std::endl;
        return -1;
    }

    std::string shaderPath = jsonData["shader"];
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail())
    {
        std::cerr << "Failed to open shader file: " << shaderPath << std::endl;
        return -1;
    }

    Renderer::SetShader(shaderPath);

    PlayPong(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
