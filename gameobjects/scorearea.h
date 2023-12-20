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
    void InitalizeComponents() override;

private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };
    bool mIsPlayerScoreArea { false };
};

class ScoreArea : public Behavior
{
public:
    ScoreArea(bool playerSide);

    int GetBehaviorID() const override { return GetIDFromBehavior<ScoreArea>(); }
    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };
};

} // namespace pong
