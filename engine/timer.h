#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace pong
{

static constexpr int kInvalid = -1;

struct TimerRequest
{
    int mGameObjectId { kInvalid };
    std::chrono::microseconds mTimeoutUs { kInvalid };
    std::function<void()> mCallback {};

    TimerRequest(int gameObjectId, std::chrono::microseconds timeoutUs, std::function<void()> callback)
        : mGameObjectId(gameObjectId),
          mTimeoutUs(timeoutUs),
          mCallback(callback)
    {
    }
};

class Timer
{
public:
    static float frameTime;

    void Init();
    void SetTimeScale(float timeScale);
    void AddTimer(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);
    void HandleTimerCallbacks();
    void Reset();

private:
    std::vector<TimerRequest> mActiveTimers {};
    std::chrono::system_clock::time_point mLastTime { std::chrono::system_clock::now() };
    float mTimeScale { 1.0f };
};

} // namespace pong

namespace pong::timer
{

extern Timer* gTimer;

Timer* GetTimerInstance();
void SetTimerInstance(Timer* timer);

void SetTimeScale(float timeScale);
void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);

} // namespace pong::timer
