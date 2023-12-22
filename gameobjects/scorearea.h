#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "scorecontroller.h"

namespace pong
{

class ScoreAreaBlueprint : public GameObjectBlueprint
{
public:
    ScoreAreaBlueprint(float width, float height, bool playerSide);
};

class ScoreArea : public Behavior
{
public:
    ScoreArea(bool playerSide);

    int GetBehaviorId() const override { return GetIdFromBehavior<ScoreArea>(); }
    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };
};

} // namespace pong
