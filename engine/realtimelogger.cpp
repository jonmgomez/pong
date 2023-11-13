// spdlog must be included before fmt. Since spdlog uses fmt, it will cause errors otherwise
#include <spdlog/spdlog.h>

#include "realtimelogger.h"

namespace pong
{

static constexpr std::chrono::milliseconds LOG_PRINT_INTERVAL_MS { 1000 };

RealTimeLogger::RealTimeLogger()
{
    mThread = std::thread(&RealTimeLogger::Run, this);
}

RealTimeLogger::~RealTimeLogger()
{
    mAlive = false;
    mThread.join();
}

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
