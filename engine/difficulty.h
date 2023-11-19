#pragma once

#include <string>

namespace pong
{

class Difficulty
{
public:
    enum class Level
    {
        Easy,
        Normal,
        Hard,
        Insane
    };

    static Level GetLevel();
    static void SetLevel(Level level);
    static std::string to_string(Difficulty::Level level);

private:
    Difficulty() = delete;
    Difficulty(const Difficulty&) = delete;
    Difficulty& operator=(const Difficulty&) = delete;
    Difficulty(Difficulty&&) = delete;
    Difficulty& operator=(Difficulty&&) = delete;
    ~Difficulty() = delete;

    static Level sLevel;
};

} // namespace pong
