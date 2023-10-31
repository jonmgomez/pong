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

public:
    void PongInit();
    void PongGameLoop();
    void CheckCollisions(GameObject* gameObject);
};

} // namespace pong
