#pragma once

#include "gameobject.h"
#include "opponent.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

class Opponent;

class Ball : public GameObject
{
public:
    void InitalizeComponents() override;
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;

    glm::vec3 GetVelocity() const;

private:
    static constexpr float BALL_START_SPEED = 1000.0f;

    Transform* mTransform { nullptr };

    glm::vec3 mVelocity { 0.0f };
    float mSpeed { BALL_START_SPEED };
    Opponent* mOpponent { nullptr };
    Sound mPaddleBounceSound {};
    Sound mWallBounceSound {};
    Sound mScoreSound {};

    void ResetBall();
};

} // namespace pong
