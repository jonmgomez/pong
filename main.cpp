#include "main.h"

#include "input.h"
#include "pong.h"
#include "renderer.h"
#include "renderutils.h"
#include "timer.h"
#include "logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace pong;

nlohmann::json OpenJsonFile(const std::string& filePath)
{
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open())
    {
        spdlog::error("Failed to open JSON file: {}", filePath);
        return nullptr;
    }

    nlohmann::json jsonData;

    try
    {
        jsonFile >> jsonData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        spdlog::error("JSON parsing error: {}", e.what());
        return nullptr;
    }

    return jsonData;
}

GLFWwindow* SetupGLFW(const nlohmann::json& jsonData)
{
    if (!glfwInit())
    {
        LogError("glfwInit() failure");
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        LogError("glfwCreateWindow() failure");
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, Input::KeyCallback);

    bool fpsCapped = true;
    if (jsonData.find("fps_capped") != jsonData.end())
    {
        fpsCapped = jsonData["fps_capped"];
    }

    if (!fpsCapped)
    {
        glfwSwapInterval(0);
    }

    if (glewInit() != GLEW_OK)
    {
        LogError("glewInit() failure");
        return nullptr;
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    LogInfo("Using OpenGL version: {}", glVersion);

    int numTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextureSlots);
    LogDebug("Texture Slots Available: {}", numTextureSlots);

    return window;
}

void PlayPong(GLFWwindow* window)
{
    Pong::Init();

    double lastTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        Renderer::Clear();

        Pong::GameLoop();

        frameCount++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    double currentTime = glfwGetTime();
    double elapsedTime = currentTime - lastTime;

    LogInfo("Elapsed time: {}", elapsedTime);
    LogInfo("Total frames: {}", frameCount);
    LogInfo("Avg framerate: {}", frameCount / elapsedTime);

    Pong::Cleanup();
    Renderer::Cleanup();
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    if (argc != 2)
    {
        LogError("Usage: {} <json_file_path>", argv[0]);
        return -1;
    }

    nlohmann::json jsonData = OpenJsonFile(argv[1]);
    if (jsonData == nullptr)
    {
        return -1;
    }

    GLFWwindow* window = SetupGLFW(jsonData);
    if (window == nullptr)
    {
        return -1;
    }

    if (jsonData.find("shader") == jsonData.end())
    {
        LogError("Config file does not contain \"shader\" key.");
        return -1;
    }

    std::string shaderPath = jsonData["shader"];
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail())
    {
        LogError("Failed to open shader file: {}", shaderPath);
        return -1;
    }

    Renderer::SetShader(shaderPath);

    PlayPong(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
