#include "scorecontroller.h"

namespace pong
{

int ScoreController::GetPlayerScore() const
{
    return mPlayerScore;
}

void ScoreController::PlayerScored()
{
    mPlayerScore++;
}

int ScoreController::GetOpponentScore() const
{
    return mOpponentScore;
}

void ScoreController::OpponentScored()
{
    mOpponentScore++;
}

} // namespace pong
