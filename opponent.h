#pragma once

#include "ball.h"
#include "gameobject.h"

namespace pong
{

class Opponent : public GameObject
{
private:
    float mSpeed { 0.0f };
    std::shared_ptr<Ball> mBall;

public:
    void OnStart() override;
    void OnUpdate() override;
};

} // namespace pong
