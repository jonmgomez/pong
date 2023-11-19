#include "random.h"

namespace pong
{

Random::Random() :
    generator(rd())
{

}

Random& Random::GetInstance()
{
    static Random instance;
    return instance;
}

template<typename T>
T Random::ValueInRange(T min, T max)
{
    static_assert(false);
}

template<>
int Random::ValueInRange<int>(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(GetInstance().generator);
}

template<>
float Random::ValueInRange<float>(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(GetInstance().generator);
}

// Uses floating value between 0.0f and 1.0f. Returns true if the value is less than or equal to the percent.
bool Random::RollPercentChance(float percent)
{
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(GetInstance().generator) <= percent;
}

bool Random::Bool()
{
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(GetInstance().generator) == 1;
}

} // namespace pong
