#pragma once

#include <concurrentqueue.h>

#include <fmt/core.h>
#include <thread>

namespace pong
{

struct LogData
{
    int mLevel { 0 };
    int mSequenceNum { 0 };
    char mMessage[512] {};
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
    RealTimeLogger()
    {
        mThread = std::thread(&RealTimeLogger::Run, this);
    }

    ~RealTimeLogger()
    {
        mAlive = false;
        mThread.join();
    }

    template<typename... Args>
    void Log(int level, const char *format, Args... args)
    {
        LogData logData;
        logData.mLevel = level;
        logData.mSequenceNum = Logger::GetNextLogNumber();
        fmt::format_to_n(logData.mMessage, 512, format, args...);

        ASSERT(mLogQueue.try_enqueue(logData));
    };

    void PrintLogs();
};

} // namespace pong
