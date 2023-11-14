#pragma once

#include <fmt/format.h>
#include <concurrentqueue.h>

#include <array>
#include <thread>

namespace pong
{

static constexpr int MAX_LOG_MESSAGE_SIZE = 512;

struct LogData
{
    int mLevel { 0 };
    int mSequenceNum { 0 };
    std::array<char, MAX_LOG_MESSAGE_SIZE> mMessage {};
};

class RealTimeLogger
{
private:
    RealTimeLogger();
    ~RealTimeLogger();
    RealTimeLogger(const RealTimeLogger&) = delete;
    RealTimeLogger& operator=(const RealTimeLogger&) = delete;
    RealTimeLogger(RealTimeLogger&&) = delete;
    RealTimeLogger& operator=(RealTimeLogger&&) = delete;

    static constexpr int MAX_LOGS = 100;

    std::thread mThread {};
    moodycamel::ConcurrentQueue<LogData> mLogQueue { MAX_LOGS };
    bool mAlive { true };

    void Run();
    void PrintLogs();

public:

    static RealTimeLogger& GetInstance();

    template<typename... Args>
    static void Log(int level, const char *format, Args... args)
    {
        LogData logData;
        logData.mLevel = level;
        logData.mSequenceNum = Logger::GetNextLogNumber();
        fmt::format_to_n(logData.mMessage.data(), MAX_LOG_MESSAGE_SIZE, format, args...);

        ASSERT(GetInstance().mLogQueue.try_enqueue(logData));
    };
};

} // namespace pong
