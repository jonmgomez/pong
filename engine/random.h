#pragma once

#include <random>

namespace pong
{

class Random
{
public:
    template<typename T>
    static T Range(T min, T max);
    static bool Percent(float percent);
    static bool Bool();

private:
    Random() = delete;
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(Random&&) = delete;
    ~Random() = delete;
};

} // namespace pong
