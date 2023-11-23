#pragma once

#include <random>

namespace pong
{

class Random
{
public:
    static Random& GetInstance();

    template<typename T>
    static T ValueInRange(T min, T max);
    static bool RollPercentChance(float percent);
    static bool Bool();

private:
    Random();
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(Random&&) = delete;

    std::random_device rd {};
    std::mt19937 generator {};
};

} // namespace pong
