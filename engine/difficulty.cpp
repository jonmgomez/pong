#include "difficulty.h"

#include "logger.h"

namespace pong
{

Difficulty::Level Difficulty::sLevel = Level::Normal;

void Difficulty::SetDifficulty(const std::string& difficulty)
{
    if (difficulty == "easy")
    {
        Difficulty::SetLevel(Difficulty::Level::Easy);
    }
    else if (difficulty == "normal")
    {
        Difficulty::SetLevel(Difficulty::Level::Normal);
    }
    else if (difficulty == "hard")
    {
        Difficulty::SetLevel(Difficulty::Level::Hard);
    }
    else if (difficulty == "insane")
    {
        Difficulty::SetLevel(Difficulty::Level::Insane);
    }
    else
    {
        LogError("Invalid difficulty: {}", difficulty);
    }
}

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
