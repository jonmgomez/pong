// spdlog must be included before fmt. Since spdlog uses fmt, it will cause errors otherwise
#include <spdlog/spdlog.h>

#include "realtimelogger.h"

#include <fmt/core.h>

#include <iostream>

#define UNWRAP(x) x[0] , x[1] , x[2] , x[3] , x[4] , x[5] , x[6] , x[7] , x[8] , x[9]

namespace pong
{

static constexpr std::chrono::milliseconds LOG_PRINT_INTERVAL_MS { 1 };

void RealTimeLogger::Run()
{
    while (mAlive)
    {
        std::this_thread::sleep_for(LOG_PRINT_INTERVAL_MS);

        PrintLogs();
    }
}

void RealTimeLogger::PrintLogs()
{
    LogData logData;

    const char* format = "[{}] {}";

    while (mLogQueue.try_dequeue(logData))
    {
        switch (logData.mLevel)
        {
        case spdlog::level::trace:
            spdlog::trace(format, logData.mSequenceNum, logData.mMessage);
            break;
        case spdlog::level::debug:
            spdlog::debug(format, logData.mSequenceNum, logData.mMessage);
            break;
        case spdlog::level::info:
            spdlog::info(format, logData.mSequenceNum, logData.mMessage);
            break;
        case spdlog::level::warn:
            spdlog::warn(format, logData.mSequenceNum, logData.mMessage);
            break;
        case spdlog::level::err:
            spdlog::error(format, logData.mSequenceNum, logData.mMessage);
            break;
        case spdlog::level::critical:
            spdlog::critical(format, logData.mSequenceNum, logData.mMessage);
            break;
        default:
            break;
        }
    }
}

} // namespace pong
