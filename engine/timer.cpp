#include "timer.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>

namespace pong
{

float Timer::frameTime = 0.0f;

void Timer::Init()
{
    const auto currentTime = std::chrono::system_clock::now();
    Timer::frameTime = (std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - mLastTime)).count();
}

void Timer::HandleTimerCallbacks()
{
    const auto timeWaitedUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - mLastTime);
    mLastTime = std::chrono::system_clock::now();

    Timer::frameTime = std::chrono::duration_cast<std::chrono::duration<float>>(timeWaitedUs).count();

    for (auto& timerRequest : mActiveTimers)
    {
        timerRequest.mTimeoutUs -= timeWaitedUs;
        if (timerRequest.mTimeoutUs.count() <= 0)
        {
            timerRequest.mCallback();
        }
    }

    mActiveTimers.erase(std::remove_if(mActiveTimers.begin(), mActiveTimers.end(), [](const auto& timerRequest) {
        return timerRequest.mTimeoutUs.count() <= 0;
    }), mActiveTimers.end());
}

void Timer::AddTimer(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback)
{
    // Internally keeps track using us. This is just in case the
    // game's framerate is uncapped. If using ms, it is possible that {timeWaited} is less then 1ms
    // and comes out to 0. This will cause the timer to not proceed.
    const auto timeoutUs = std::chrono::duration_cast<std::chrono::microseconds>(timeout);
    mActiveTimers.emplace_back(gameObjectId, timeoutUs, callback);
}

void Timer::Reset()
{
    mActiveTimers.clear();
}

} // namespace pong
