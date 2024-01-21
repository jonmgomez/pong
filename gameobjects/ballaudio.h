#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "sound.h"

namespace pong
{

class BallAudio : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<BallAudio>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;

    void HitScoreArea();
    void HitPaddle();
    void HitWall();

private:
    Transform* mTransform { nullptr };
    Sound mPaddleBounceSound {};
    Sound mWallBounceSound {};
    Sound mScoreSound {};
};

} // namespace pong
