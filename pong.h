#pragma once

#include "gameobject.h"

#include <vector>

namespace pong
{

class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};

public:
    void PongInit();
    void PongGameLoop();
};

} // namespace pong
