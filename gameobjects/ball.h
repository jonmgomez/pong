#pragma once

#include "gameobject.h"

namespace pong
{

class Ball : public GameObject
{
private:
    static constexpr float BALL_START_SPEED = 4.0f;

    glm::vec3 mVelocity { BALL_START_SPEED, BALL_START_SPEED, 0.0f };
    float mSpeed { BALL_START_SPEED };

    void ResetBall();

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
};

} // namespace pong
