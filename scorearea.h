#pragma once

#include "gameobject.h"

namespace pong
{

class ScoreArea : public GameObject
{
private:
    bool mIsPlayerScoreArea { false };

public:
    ScoreArea(float width, float height, bool playerSide);

    void OnCollisionStart(GameObject& other) override;
};

} // namespace pong
