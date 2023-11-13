#pragma once

#include <concurrentqueue.h>
#include <spdlog/spdlog.h>

#ifndef STB_SPRINTF_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION
#endif

#ifndef STB_SPRINTF_STATIC
#define STB_SPRINTF_STATIC
#endif

#pragma warning(push, 0)
#include <stb_sprintf.h>
#pragma warning(pop)

#include <array>
#include <thread>

namespace pong
{

struct LogData
{
    int mLevel { -1 };
    char mFormat[512] {};
    std::array<std::string, 10> mArgs {};
};

class RealTimeLogger
{
private:
    static constexpr int MAX_LOGS = 100;

    static int sLogNumber;

    std::thread mThread {};
    moodycamel::ConcurrentQueue<LogData> mLogQueue { MAX_LOGS };
    bool mAlive { true };

    void Run();

public:
    void Start();
    void Join();

    template<typename... Args>
    void Log(int level, const char *format, Args... args)
    {
        std::string temp = format;
        temp = "[{}] " + temp;
        format = temp.c_str();

        LogData logData;
        logData.mLevel = level;

        stbsp_snprintf(logData.mFormat, sizeof(logData.mFormat), format, args...);

        logData.mArgs[0] = std::to_string(sLogNumber++);
        int i = 1;
        ((logData.mArgs[i++] = std::to_string(args)), ...);

        mLogQueue.try_enqueue(logData);
    };

    void PrintLogs();
};

} // namespace pong
