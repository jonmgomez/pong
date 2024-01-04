#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "opponent.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

class Opponent;

class Ball : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<Ball>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;

    glm::vec3 GetVelocity() const;

private:
    static constexpr float BALL_START_SPEED = 1000.0f;

    Transform* mTransform { nullptr };

    glm::vec3 mVelocity { 0.0f };
    float mStartSpeed { BALL_START_SPEED };
    float mSpeed { mStartSpeed };
    Opponent* mOpponent { nullptr };
    Sound mPaddleBounceSound {};
    Sound mWallBounceSound {};
    Sound mScoreSound {};

    void ResetBall();

    friend class ComponentDeserializer;
};

} // namespace pong
