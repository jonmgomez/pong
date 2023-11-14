#pragma once

#include "realtimelogger.h"

#include <fmt/core.h>

#include <atomic>

namespace pong
{

class Logger
{
public:
    static Logger& Logger::GetInstance();
    static int Logger::GetNextLogNumber();

    template<typename... Args>
    void Log(int level, const char* format, Args... args)
    {
        // Prepend the sequence number to the log message
        std::string temp = format;
        temp = "[{}] " + temp;
        format = temp.c_str();

        const int logNum = Logger::GetNextLogNumber();
        switch (level)
        {
        case spdlog::level::trace:
            spdlog::trace(format, logNum, args...);
            break;
        case spdlog::level::debug:
            spdlog::debug(format, logNum, args...);
            break;
        case spdlog::level::info:
            spdlog::info(format, logNum, args...);
            break;
        case spdlog::level::warn:
            spdlog::warn(format, logNum, args...);
            break;
        case spdlog::level::err:
            spdlog::error(format, logNum, args...);
            break;
        case spdlog::level::critical:
            spdlog::critical(format, logNum, args...);
            break;
        default:
            ASSERT(false);
            break;
        }
    };

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static std::atomic<int> Logger::sLogNumber;
};

template<typename... Args>
void LogDebug(const char* format, Args... args)
{
    Logger::GetInstance().Log(spdlog::level::debug, format, args...);
}

template<typename... Args>
void LogInfo(const char* format, Args... args)
{
    Logger::GetInstance().Log(spdlog::level::info, format, args...);
}

template<typename... Args>
void LogWarning(const char* format, Args... args)
{
    Logger::GetInstance().Log(spdlog:level::warn, format, args...);
}

template<typename... Args>
void LogCritical(const char* format, Args... args)
{
    Logger::GetInstance().Log(spdlog::level::critical, format, args...);
}

template<typename... Args>
void LogError(const char* format, Args... args)
{
    Logger::GetInstance().Log(spdlog::level::err, format, args...);
}

template<typename... Args>
void RealTimeLogDebug(const char* format, Args... args)
{
    RealTimeLogger::GetInstance().Log(spdlog::level::debug, format, args...);
}

template<typename... Args>
void RealTimeLogInfo(const char* format, Args... args)
{
    RealTimeLogger::GetInstance().Log(spdlog::level::info, format, args...);
}

template<typename... Args>
void RealTimeLogWarning(const char* format, Args... args)
{
    RealTimeLogger::GetInstance().Log(spdlog::level::warn, format, args...);
}

template<typename... Args>
void RealTimeLogCritical(const char* format, Args... args)
{
    RealTimeLogger::GetInstance().Log(spdlog::level::critical, format, args...);
}

template<typename... Args>
void RealTimeLogError(const char* format, Args... args)
{
    RealTimeLogger::GetInstance().Log(spdlog::level::err, format, args...);
}

} // namespace pong
