#include "random.h"

namespace pong
{

static std::random_device rd;
static std::mt19937 generator(rd());

template<typename T>
T Random::Range(T min, T max)
{
    static_assert(false);
}

template<>
int Random::Range<int>(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator);
}

template<>
float Random::Range<float>(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

// Uses floating value between 0.0f and 1.0f. Returns true if the value is less than or equal to the percent.
bool Random::Percent(float percent)
{
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(generator) <= percent;
}

bool Random::Bool()
{
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(generator) == 1;
}

} // namespace pong
