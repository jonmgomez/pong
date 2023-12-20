#include "scorearea.h"

#include "colliderbox.h"
#include "pong.h"
#include "rectangle.h"
#include "scorecontroller.h"
#include "logger.h"

#include <spdlog/spdlog.h>

namespace pong
{

ScoreAreaBlueprint::ScoreAreaBlueprint(float width, float height, bool playerSide) :
    mWidth { width },
    mHeight { height },
    mIsPlayerScoreArea { playerSide }
{
    SetInstanceName("ScoreArea");
    InitalizeComponents();
}

void ScoreAreaBlueprint::InitalizeComponents()
{
    AddComponent<Transform>();
    AddComponent<Rectangle>(mWidth, mHeight);
    AddComponent<ColliderBox>(mWidth, mHeight);
    AddComponent<ScoreArea>(mIsPlayerScoreArea);
}

ScoreArea::ScoreArea(bool playerSide) :
    mIsPlayerScoreArea { playerSide }
{
}

void ScoreArea::OnStart()
{
    mScoreController = Pong::FindComponentOfBehavior<ScoreController>();
    if (mScoreController == nullptr)
    {
        spdlog::error("ScoreController instance not found!");
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
