#include "scorearea.h"

#include "colliderbox.h"
#include "pong.h"
#include "rectangle.h"
#include "scorecontroller.h"
#include "logger.h"

namespace pong
{

ScoreArea::ScoreArea(bool playerSide) :
    mIsPlayerScoreArea { playerSide }
{
}

void ScoreArea::OnStart()
{
    mScoreController = Pong::FindComponentOfType<ScoreController>();
    if (mScoreController == nullptr)
    {
        LogError("ScoreController instance not found!");
    }
}

void ScoreArea::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "Ball")
    {
        ASSERT(mScoreController != nullptr);

        if (mIsPlayerScoreArea)
        {
            RealTimeLogInfo("Player scored!");
            mScoreController->PlayerScored();
        }
        else
        {
            RealTimeLogInfo("Opponent scored!");
            mScoreController->OpponentScored();
        }

        RealTimeLogInfo("New Score: P {} - O {}", mScoreController->GetPlayerScore(), mScoreController->GetOpponentScore());
    }
}

} // namespace pong
