#pragma once

#include "ballaudio.h"
#include "ballmovement.h"
#include "behavior.h"
#include "gameobject.h"

namespace pong
{

class BallCollisions : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<BallCollisions>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    BallMovement* mBall { nullptr };
    BallAudio* mBallAudio { nullptr };
};

} // namespace pong
