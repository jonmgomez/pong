#pragma once

#include "collisionmanager.h"
#include "gameobject.h"

#include <memory>
#include <vector>

namespace pong
{

class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    CollisionManager mCollisionManager {};

public:
    void PongInit();
    void PongGameLoop();
};

} // namespace pong
