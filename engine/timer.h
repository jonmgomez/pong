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
    int mTimeoutUs { kInvalid };
    std::function<void()> mCallback {};

    TimerRequest(int gameObjectId, int timeoutUs, std::function<void()> callback)
        : mGameObjectId(gameObjectId),
          mTimeoutUs(timeoutUs),
          mCallback(callback)
    {
    }
};

class Timer
{
private:
    std::vector<TimerRequest> mActiveTimers {};
    std::chrono::system_clock::time_point mLastTime { std::chrono::system_clock::now() };

public:
    static float frameTime;

    void AddTimer(int gameObjectId, int timeoutMs, std::function<void()> callback);
    void HandleTimerCallbacks();
};

} // namespace pong
