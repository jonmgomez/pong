#pragma once

#include "gameobject.h"

namespace pong
{

class Ball : public GameObject
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;

private:
    static constexpr float BALL_START_SPEED = 1000.0f;

    glm::vec3 mVelocity { BALL_START_SPEED, BALL_START_SPEED, 0.0f };
    float mSpeed { BALL_START_SPEED };

    void ResetBall();
};

} // namespace pong
