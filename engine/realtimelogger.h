#pragma once

#include <concurrentqueue.h>

#include <fmt/core.h>
#include <thread>

namespace pong
{

static constexpr int MAX_LOG_MESSAGE_SIZE = 512;

struct LogData
{
    int mLevel { 0 };
    int mSequenceNum { 0 };
    char mMessage[MAX_LOG_MESSAGE_SIZE] {};
};

class RealTimeLogger
{
private:
    static constexpr int MAX_LOGS = 100;

    std::thread mThread {};
    moodycamel::ConcurrentQueue<LogData> mLogQueue { MAX_LOGS };
    bool mAlive { true };

    void Run();

public:
    RealTimeLogger();
    ~RealTimeLogger();

    template<typename... Args>
    void Log(int level, const char *format, Args... args)
    {
        LogData logData;
        logData.mLevel = level;
        logData.mSequenceNum = Logger::GetNextLogNumber();
        fmt::format_to_n(logData.mMessage, MAX_LOG_MESSAGE_SIZE, format, args...);

        ASSERT(mLogQueue.try_enqueue(logData));
    };

    void PrintLogs();
};

} // namespace pong
