#include "engine.h"

#include "config.h"
#include "input.h"
#include "logger.h"
#include "pong.h"
#include "renderer.h"
#include "utils.h"

#include <chrono>
#include <fstream>
#include <string>

namespace pong
{

Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

void Engine::Init(const std::string& configPath)
{
    ASSERT(Config::LoadConfig(configPath));

    ApplicationWindow::Init();
    Renderer::Init();
    Input::Init();

    const auto targetFPSJson = Config::GetJsonValue("target_fps");
    if (targetFPSJson.has_value() && targetFPSJson.value().is_number_integer())
    {
        if (targetFPSJson.value() > 0)
        {
            Engine::SetTargetFPS(targetFPSJson.value());
            LogInfo("Target FPS: {}", mTargetFPS);
        }
        else
        {
            LogInfo("Target FPS: Unlimited");
        }
    }
    else
    {
        ApplicationWindow::SetVSync(true);
        LogInfo("Target FPS not specified or invalid. Using refresh rate.");
    }

    Pong::Init();
}

void Engine::RunApplication()
{
    int frameCount = 0;
    const auto windowStartTime = std::chrono::high_resolution_clock::now();

    while (!ApplicationWindow::ShouldClose())
    {
        if (IsNextFrameReady())
        {
            frameCount++;

            Renderer::Clear();
            Pong::GameLoop();
            ApplicationWindow::SwapBuffers();
        }
    }

    const auto windowEndTime = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsedTime = windowEndTime - windowStartTime;

    LogInfo("Elapsed time: {}s", roundf(static_cast<float>(elapsedTime.count()) * 100.0f) / 100.0f);
    LogInfo("Total frames: {}", frameCount);
    LogInfo("Avg framerate: {} FPS", static_cast<int>(frameCount / elapsedTime.count()));
}

bool Engine::IsNextFrameReady()
{
    if (ApplicationWindow::IsVSyncActive())
    {
        mLastFrameTimeStamp = std::chrono::high_resolution_clock::now();
        return true;
    }

    const auto now = std::chrono::high_resolution_clock::now();
    const auto timeSinceLastFrame = std::chrono::duration_cast<std::chrono::nanoseconds>(now - mLastFrameTimeStamp);

    if (timeSinceLastFrame >= mTimePerFrame)
    {
        mLastFrameTimeStamp = now;
        return true;
    }

    return false;
}

void Engine::Cleanup()
{
    if (Config::GetValue("save_config_settings", true))
    {
        Config::SaveConfig();
    }

    Pong::Cleanup();
    Renderer::Cleanup();
    ApplicationWindow::Cleanup();
}

int Engine::GetTargetFPS()
{
    return GetInstance().mTargetFPS;
}

void Engine::SetTargetFPS(int fps)
{
    ASSERT(fps > 0);
    GetInstance().mTargetFPS = fps;
    GetInstance().mTimePerFrame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / GetInstance().mTargetFPS;
    Config::SetValue("target_fps", fps);
}

void Engine::QuitApplication()
{
    ApplicationWindow::SetShouldCloseWindow();
}

} // namespace pong
