#pragma once

#include "realtimelogger.h"

#include <fmt/core.h>

#include <atomic>

namespace pong
{

class Logger
{
public:
    static int GetNextLogNumber()
    {
        return sLogNumber++;
    }

    template<typename... Args>
    void Log(int level, const char* format, Args... args)
    {
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
            break;
        }
    };

private:
    inline static int sLogNumber { 0 };
};

inline std::unique_ptr<Logger> gLogger { nullptr };
inline std::unique_ptr<RealTimeLogger> gRTLogger { nullptr };

template<typename... Args>
void Log(int level, const char* format, Args... args)
{
    if (gLogger != nullptr)
    {
        gLogger->Log(level, format, args...);
    }
};

template<typename... Args>
void RealTimeLog(int level, const char* format, Args... args)
{
    if (gRTLogger != nullptr)
    {
        gRTLogger->Log(level, format, args...);
    }
}

} // namespace pong
