#pragma once

#include "ball.h"
#include "gameobject.h"

namespace pong
{

class Opponent : public GameObject
{
private:
    glm::vec3 mVelocity { 0.0f };
    std::shared_ptr<Ball> mBall { nullptr };

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;
};

} // namespace pong
