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

void Engine::Init(const std::string& configPath)
{
    ASSERT(Config::LoadConfig(configPath));

    application::SetWindowInstance(&mApplicationWindow);
    input::SetInputInstance(&mInput);
    game::SetPongInstance(&mPong);

    mApplicationWindow.Init();
    mApplicationWindow.SetWindowTitle("Pong");
    mApplicationWindow.SetWindowIcon(Config::GetValue<std::string>("window_icon"));

    mRenderer.Init(&mPong.GetComponentManager());

    mInput.Init();

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
        mApplicationWindow.SetVSync(true);
        LogInfo("Target FPS not specified or invalid. Using refresh rate.");
    }

    mPong.Init();
}

void Engine::RunApplication()
{
    int frameCount = 0;
    const auto windowStartTime = std::chrono::high_resolution_clock::now();

    while (!mApplicationWindow.ShouldClose())
    {
        if (IsNextFrameReady())
        {
            frameCount++;

            mRenderer.Clear();
            mPong.GameLoop();
            mRenderer.DrawAll();
            mApplicationWindow.SwapBuffers();
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
    if (mApplicationWindow.IsVSyncActive())
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

    mPong.Cleanup();
    mRenderer.Cleanup();
    mApplicationWindow.Cleanup();
}

int Engine::GetTargetFPS()
{
    return mTargetFPS;
}

void Engine::SetTargetFPS(int fps)
{
    ASSERT(fps > 0);
    mTargetFPS = fps;
    mTimePerFrame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / mTargetFPS;
    Config::SetValue("target_fps", fps);
}

void Engine::QuitApplication()
{
    mApplicationWindow.SetShouldCloseWindow();
}

} // namespace pong

namespace pong::engine
{

Engine* gEngine { nullptr };

Engine* GetEngineInstance()
{
    ASSERT(gEngine != nullptr);
    return gEngine;
}

void SetEngineInstance(Engine* engine)
{
    gEngine = engine;
}

int GetTargetFPS()
{
    return GetEngineInstance()->GetTargetFPS();
}

void SetTargetFPS(const int fps)
{
    GetEngineInstance()->SetTargetFPS(fps);
}

void QuitApplication()
{
    GetEngineInstance()->QuitApplication();
}

} // namespace pong::engine
