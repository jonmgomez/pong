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
private:
    std::vector<TimerRequest> mActiveTimers {};
    std::chrono::system_clock::time_point mLastTime { std::chrono::system_clock::now() };

public:
    static float frameTime;

    void AddTimer(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);
    void HandleTimerCallbacks();
};

} // namespace pong
