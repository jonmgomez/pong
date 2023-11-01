#pragma once

#include "gameobject.h"

#include <vector>

namespace pong
{

class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    std::vector<std::vector<GameObject*>>mCheckedCollisions {};
    std::vector<std::vector<GameObject*>>mCurrentlyColliding {};

public:
    void PongInit();
    void PongGameLoop();
};

} // namespace pong
