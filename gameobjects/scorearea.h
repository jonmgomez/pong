#pragma once

#include "gameobject.h"
#include "scorecontroller.h"

namespace pong
{

class ScoreArea : public GameObject
{
public:
    ScoreArea(float width, float height, bool playerSide);

    void InitalizeComponents() override;
    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
