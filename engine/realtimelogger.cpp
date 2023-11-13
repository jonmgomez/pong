#include "realtimelogger.h"

#include <spdlog/spdlog.h>

#include <iostream>

#define UNWRAP(x) x[0] , x[1] , x[2] , x[3] , x[4] , x[5] , x[6] , x[7] , x[8] , x[9]

namespace pong
{

static constexpr std::chrono::milliseconds LOG_PRINT_INTERVAL { 1000 };

int RealTimeLogger::sLogNumber = 0;

void RealTimeLogger::Start()
{
    mThread = std::thread(&RealTimeLogger::Run, this);
}

void RealTimeLogger::Join()
{
    mAlive = false;
    mThread.join();
}

void RealTimeLogger::Run()
{
    while (mAlive)
    {
        std::this_thread::sleep_for(LOG_PRINT_INTERVAL);

        PrintLogs();
    }
}

void RealTimeLogger::PrintLogs()
{
    LogData logData;
    while (mLogQueue.try_dequeue(logData))
    {
        switch (logData.mLevel)
        {
        case spdlog::level::trace:
            spdlog::trace(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        case spdlog::level::debug:
            spdlog::debug(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        case spdlog::level::info:
            spdlog::info(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        case spdlog::level::warn:
            spdlog::warn(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        case spdlog::level::err:
            spdlog::error(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        case spdlog::level::critical:
            spdlog::critical(logData.mFormat, UNWRAP(logData.mArgs));
            break;
        default:
            break;
        }
    }
}

} // namespace pong
