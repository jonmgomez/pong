#include "timer.h"

#include <algorithm>
#include <chrono>
#include <memory>

namespace pong
{

static constexpr int MS_TO_US = 1000;

void Timer::HandleTimerCallbacks()
{
    const auto timeWaited = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - mLastTime);
    mLastTime = std::chrono::system_clock::now();

    const int timeWaitedUs = static_cast<int>(timeWaited.count());
    for (auto& timerRequest : mActiveTimers)
    {
        timerRequest->mTimeoutUs -= timeWaitedUs;
        if (timerRequest->mTimeoutUs <= 0)
        {
            timerRequest->mCallback();
        }
    }

    mActiveTimers.erase(std::remove_if(mActiveTimers.begin(), mActiveTimers.end(), [](const auto& timerRequest) {
        return timerRequest->mTimeoutUs <= 0;
    }), mActiveTimers.end());
}

void Timer::AddTimer(int gameObjectId, int timeoutMs, std::function<void()> callback)
{
    // Interface uses ms but internally keeps track using us. This is just in case the
    // game's framerate is uncapped. It is possible that {timeWaited} is less then 1ms
    // and comes out to 0 then the timer will not proceed.
    const int timeoutUs = timeoutMs * MS_TO_US;
    auto timerRequest = std::make_shared<TimerRequest>(gameObjectId, timeoutUs, callback);
    mActiveTimers.push_back(timerRequest);
}

} // namespace pong
