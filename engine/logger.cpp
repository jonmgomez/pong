#include "logger.h"

#include <atomic>

namespace pong
{

std::atomic<int> Logger::sLogNumber { 0 };

Logger& Logger::GetInstance()
{
    static Logger instance;
    return instance;
};

int Logger::GetNextLogNumber()
{
    return sLogNumber++;
};

} // namespace pong
