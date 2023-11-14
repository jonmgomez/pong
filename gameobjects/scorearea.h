#pragma once

#include "gameobject.h"
#include "scorecontroller.h"

namespace pong
{

class ScoreArea : public GameObject
{
public:
    ScoreArea(float width, float height, bool playerSide);

    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;

private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };
};

} // namespace pong
