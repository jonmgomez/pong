#pragma once

#include "gameobject.h"

namespace pong
{

class Opponent : public GameObject
{
private:
    float mSpeed { 0.0f };

public:
    void OnStart() override;
    void OnUpdate() override;
};

} // namespace pong
