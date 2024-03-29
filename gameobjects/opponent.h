#pragma once

#include "ballmovement.h"
#include "behavior.h"
#include "colliderbox.h"
#include "gameobject.h"
#include "transform.h"

namespace pong
{

class BallMovement;

class Opponent : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<Opponent>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

    void OnBallVelocityChange(const glm::vec3& velocity);

private:
    static constexpr float OPPONENT_MAX_SPEED = 1200.0f;

    void SetDifficultySettings();
    void PredictBallPostion();

    Transform* mTransform { nullptr };
    ColliderBox* mCollider { nullptr };

    glm::vec3 mTargetPosition { 0.0f };
    glm::vec3 mVelocity { 0.0f };
    float mSpeed { OPPONENT_MAX_SPEED };

    BallMovement* mBall { nullptr };
    bool mChasingBall { false };

    float mTopWallBound { 0.0f };
    float mBottomWallBound { 0.0f };

    // Difficulty settings
    int mDecisionTimeLowerBoundMs = 50;
    int mDecisionTimeUpperBoundMs = 250;
    float mBaseMissChance = 0.1f;

    friend class ComponentDeserializer;
};

} // namespace pong
