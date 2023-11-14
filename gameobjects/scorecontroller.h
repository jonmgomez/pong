#pragma once

#include "gameobject.h"

namespace pong
{

class ScoreController : public GameObject
{
public:
    int GetPlayerScore() const;
    void PlayerScored();
    int GetOpponentScore() const;
    void OpponentScored();

private:
    int mPlayerScore { 0 };
    int mOpponentScore { 0 };
};

} // namespace pong
