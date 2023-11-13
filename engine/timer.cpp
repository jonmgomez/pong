#include "timer.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>

namespace pong
{

static constexpr int MS_TO_US = 1000;
static constexpr int S_TO_US = 1000000;

float Timer::frameTime = 1.0f;

void Timer::HandleTimerCallbacks()
{
    const auto timeWaited = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - mLastTime);
    mLastTime = std::chrono::system_clock::now();

    Timer::frameTime = static_cast<float>(timeWaited.count()) / static_cast<float>(S_TO_US);

    const int timeWaitedUs = static_cast<int>(timeWaited.count());
    for (auto& timerRequest : mActiveTimers)
    {
        timerRequest.mTimeoutUs -= timeWaitedUs;
        if (timerRequest.mTimeoutUs <= 0)
        {
            timerRequest.mCallback();
        }
    }

    mActiveTimers.erase(std::remove_if(mActiveTimers.begin(), mActiveTimers.end(), [](const auto& timerRequest) {
        return timerRequest.mTimeoutUs <= 0;
    }), mActiveTimers.end());
}

void Timer::AddTimer(int gameObjectId, int timeoutMs, std::function<void()> callback)
{
    // Interface uses ms but internally keeps track using us. This is just in case the
    // game's framerate is uncapped. If using ms, it is possible that {timeWaited} is less then 1ms
    // and comes out to 0. This will cause the timer to not proceed.
    const int timeoutUs = timeoutMs * MS_TO_US;
    mActiveTimers.emplace_back(gameObjectId, timeoutUs, callback);
}

} // namespace pong
