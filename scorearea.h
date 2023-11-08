#pragma once

#include "gameobject.h"
#include "scorecontroller.h"

namespace pong
{

class ScoreArea : public GameObject
{
private:
    bool mIsPlayerScoreArea { false };
    ScoreController* mScoreController { nullptr };

public:
    ScoreArea(float width, float height, bool playerSide);

    void OnStart() override;
    void OnCollisionStart(GameObject& other) override;
};

} // namespace pong
