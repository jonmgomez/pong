#pragma once

#include "applicationwindow.h"
#include "input.h"
#include "pong.h"
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

    int GetTargetFPS() const;
    void SetTargetFPS(int fps);

    void QuitApplication();

private:
    bool IsNextFrameReady();

    Renderer mRenderer {};
    ApplicationWindow mApplicationWindow {};
    Input mInput { mRenderer, mApplicationWindow };
    Pong mPong {};

    int mTargetFPS { 60 };
    std::chrono::nanoseconds mTimePerFrame { 0 };
    std::chrono::steady_clock::time_point mLastFrameTimeStamp { std::chrono::steady_clock::now() };
};

} // namespace pong

namespace pong::globals::engine
{

extern Engine* gEngine;

Engine* GetEngineInstance();
void SetEngineInstance(Engine* engine);

int GetTargetFPS();
void SetTargetFPS(const int fps);
void QuitApplication();

} // namespace pong::globals::engine
