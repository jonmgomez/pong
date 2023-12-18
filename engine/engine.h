#pragma once

#include "applicationwindow.h"
#include "renderer.h"

#include <string>

namespace pong
{

class Engine
{
public:
    static Engine& GetInstance();

    void Init(const std::string& configPath);
    void RunApplication();
    void Cleanup();

    static int GetTargetFPS();
    static void SetTargetFPS(int fps);

    static void QuitApplication();

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    bool IsNextFrameReady();

    int mTargetFPS { 60 };
    std::chrono::nanoseconds mTimePerFrame { 0 };
    std::chrono::steady_clock::time_point mLastFrameTimeStamp { std::chrono::steady_clock::now() };
};

} // namespace pong
