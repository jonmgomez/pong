#include "difficulty.h"

namespace pong
{

Difficulty::Level Difficulty::sLevel = Level::Normal;

Difficulty::Level Difficulty::GetLevel()
{
    return sLevel;
}

void Difficulty::SetLevel(Level level)
{
    sLevel = level;
}

std::string Difficulty::to_string(Difficulty::Level level)
{
    switch (level)
    {
        case Difficulty::Level::Easy:
            return "Easy";
        case Difficulty::Level::Normal:
            return "Normal";
        case Difficulty::Level::Hard:
            return "Hard";
        case Difficulty::Level::Insane:
            return "Insane";
        default:
            return "Unknown";
    }
}

} // namespace pong
