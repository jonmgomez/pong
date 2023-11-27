#include "main.h"

#include "config.h"
#include "difficulty.h"
#include "input.h"
#include "pong.h"
#include "renderer.h"
#include "renderutils.h"
#include "timer.h"
#include "logger.h"
#include "utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

#include "audio.h"

using namespace pong;


#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

GLFWwindow* SetupGLFW()
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
    (void)window;
    Pong::Init();

    // Is the framerate managed by glfw
    bool fpsLimitManaged = true;
    int targetFPS = 60;


    const auto targetFPSJson = Config::GetJsonValue("target_fps");
    if (targetFPSJson.has_value() && targetFPSJson.value().is_number_integer())
    {
        glfwSwapInterval(0);
        if (targetFPSJson.value() > 0)
        {
            fpsLimitManaged = false;
            targetFPS = targetFPSJson.value();
            LogInfo("Target FPS: {}", targetFPS);
        }
        else
        {
            LogInfo("Target FPS: Unlimited");
        }
    }
    else
    {
        // Let glfw tie framerate to refresh rate
        glfwSwapInterval(1);
        LogInfo("Target FPS not specified or invalid. Using refresh rate.");
    }

    const auto nanoSecondsPerFrame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / targetFPS;
    std::chrono::nanoseconds takenTime(nanoSecondsPerFrame);

    int frameCount = 0;
    const auto windowStartTime = std::chrono::high_resolution_clock::now();
    auto start = windowStartTime;

    // while (!glfwWindowShouldClose(window))
    // {
    //     if (fpsLimitManaged || takenTime >= nanoSecondsPerFrame)
    //     {
    //         takenTime = std::chrono::nanoseconds(0);

    //         Renderer::Clear();

    //         Pong::GameLoop();

    //         frameCount++;

    //         glfwSwapBuffers(window);
    //         glfwPollEvents();
    //     }
    //     else
    //     {
    //         const auto now = std::chrono::high_resolution_clock::now();
    //         takenTime += std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
    //         start = now;
    //     }
    // }

    const auto windowEndTime = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsedTime = windowEndTime - windowStartTime;

    LogInfo("Elapsed time: {}s", roundf(static_cast<float>(elapsedTime.count()) * 100.0f) / 100.0f);
    LogInfo("Total frames: {}", frameCount);
    LogInfo("Avg framerate: {} FPS", static_cast<int>(frameCount / elapsedTime.count()));

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

    if (!Config::LoadConfig(argv[1]))
    {
        return -1;
    }

    GLFWwindow* window = SetupGLFW();
    if (window == nullptr)
    {
        return -1;
    }

    const auto shaderKey = Config::GetJsonValue("shader");
    if (!shaderKey.has_value())
    {
        LogError("\"shader\" JSON key not found");
        return -1;
    }

    if (!shaderKey.value().is_string())
    {
        LogError("\"shader\" JSON key is not a string");
        return -1;
    }

    const std::string shaderPath = shaderKey.value();
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail())
    {
        LogError("Failed to open shader file: {}", shaderPath);
        return -1;
    }

    Renderer::SetShader(shaderPath);

    std::string difficulty = Config::GetValue<std::string>("difficulty", "normal");
    if (difficulty == "easy")
    {
        Difficulty::SetLevel(Difficulty::Level::Easy);
    }
    else if (difficulty == "normal")
    {
        Difficulty::SetLevel(Difficulty::Level::Normal);
    }
    else if (difficulty == "hard")
    {
        Difficulty::SetLevel(Difficulty::Level::Hard);
    }
    else if (difficulty == "insane")
    {
        Difficulty::SetLevel(Difficulty::Level::Insane);
    }
    else
    {
        LogError("Invalid difficulty: {}", difficulty);
    }
    LogInfo("Set Difficulty: {}", Difficulty::to_string(Difficulty::GetLevel()));

    printf("Test");

    ReadFile();

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
    }

    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2; // Stereo
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    const int numDevices = Pa_GetDeviceCount();
    if( numDevices < 0 )
    {
        printf( "ERROR: Pa_CountDevices returned 0x%x\n", numDevices );
        err = numDevices;
    }

    const   PaDeviceInfo *deviceInfo;
    for(int i = 0; i < numDevices; i++)
    {
        deviceInfo = Pa_GetDeviceInfo( i );
        std::cout << "Device " << i << ": {" << deviceInfo->name << "}\n";
    }

    PaStream* stream;
    err = Pa_OpenStream(&stream, nullptr, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, AudioCallback, nullptr);
    if (err != paNoError) {
        std::cerr << "PortAudio stream opening failed: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream starting failed: " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
    }

    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream stopping failed: " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream closing failed: " << Pa_GetErrorText(err) << std::endl;
    }

    Pa_Terminate();

    // PlayPong(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
