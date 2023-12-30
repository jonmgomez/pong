#pragma once

#include "logger.h"
#include "utils.h"

#include <fmt/format.h>
#include <concurrentqueue.h>

#include <array>
#include <thread>

namespace pong
{

static constexpr int MAX_LOGS = 1000;
static constexpr int MAX_LOG_MESSAGE_SIZE = 512;

struct LogData
{
    int mLevel { 0 };
    int mSequenceNum { 0 };
    std::array<char, MAX_LOG_MESSAGE_SIZE> mMessage {};
};

class RealTimeLogger
{
public:
    static RealTimeLogger& GetInstance();

    template<typename... Args>
    void Log(int level, const char *format, Args... args)
    {
        LogData logData;
        logData.mLevel = level;
        logData.mSequenceNum = Logger::GetNextLogNumber();
        const auto result = fmt::format_to_n(logData.mMessage.data(), MAX_LOG_MESSAGE_SIZE,
                                             format, std::forward<Args>(args)...);

        ASSERT(result.size < MAX_LOG_MESSAGE_SIZE);

        ASSERT(GetInstance().mLogQueue.try_enqueue(logData));
    };

private:
    RealTimeLogger();
    ~RealTimeLogger();
    RealTimeLogger(const RealTimeLogger&) = delete;
    RealTimeLogger& operator=(const RealTimeLogger&) = delete;
    RealTimeLogger(RealTimeLogger&&) = delete;
    RealTimeLogger& operator=(RealTimeLogger&&) = delete;

    std::thread mThread {};
    moodycamel::ConcurrentQueue<LogData> mLogQueue { MAX_LOGS };
    bool mAlive { true };

    void Run();
    void PrintLogs();
};

} // namespace pong
