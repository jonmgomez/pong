#pragma once

#include "gameobject.h"

#include <vector>

class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};

public:
    void PongInit();
    void PongGameLoop();
};
