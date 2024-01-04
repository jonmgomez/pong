#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "scorecontroller.h"

namespace pong
{

class ScoreArea : public Behavior
{
public:
    ScoreArea() = default;
    ScoreArea(bool playerSide);

    int GetBehaviorId() const override { return GetIdFromBehavior<ScoreArea>(); }
    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };

    friend class ComponentDeserializer;
};

} // namespace pong
