#pragma once

#include "applicationwindow.h"
#include "input.h"
#include "renderer.h"

#include <string>

namespace pong
{

class Engine
{
public:
    Engine() = default;
    ~Engine() = default;

    void Init(const std::string& configPath);
    void RunApplication();
    void Cleanup();

    int GetTargetFPS();
    void SetTargetFPS(int fps);

    void QuitApplication();

private:
    bool IsNextFrameReady();

    ApplicationWindow mApplicationWindow {};
    Input mInput { Renderer::GetInstance(), mApplicationWindow };

    int mTargetFPS { 60 };
    std::chrono::nanoseconds mTimePerFrame { 0 };
    std::chrono::steady_clock::time_point mLastFrameTimeStamp { std::chrono::steady_clock::now() };
};

} // namespace pong

namespace pong::engine
{

extern Engine* gEngine;

Engine* GetEngineInstance();
void SetEngineInstance(Engine* engine);

int GetTargetFPS();
void SetTargetFPS(const int fps);
void QuitApplication();

} // namespace pong::engine
