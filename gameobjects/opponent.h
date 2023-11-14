#pragma once

#include "ball.h"
#include "gameobject.h"

namespace pong
{

class Opponent : public GameObject
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

private:
    glm::vec3 mVelocity { 0.0f };
    Ball* mBall { nullptr };
};

} // namespace pong
