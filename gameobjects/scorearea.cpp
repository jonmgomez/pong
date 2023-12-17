#include "scorearea.h"

#include "colliderbox.h"
#include "pong.h"
#include "rectangle.h"
#include "scorecontroller.h"
#include "logger.h"

#include <spdlog/spdlog.h>

namespace pong
{

ScoreArea::ScoreArea(float width, float height, bool playerSide)
{
    mColliderBox = std::make_unique<ColliderBox>(width, height);
    mIsPlayerScoreArea = playerSide;
    SetInstanceName("ScoreArea");
}

void ScoreArea::InitalizeComponents()
{
    AddComponent<Transform>();
    AddComponent<Rectangle>(mColliderBox->GetWidth(), mColliderBox->GetHeight());
    AddComponent<ColliderBox>(mColliderBox->GetWidth(), mColliderBox->GetHeight());
}

void ScoreArea::OnStart()
{
    mScoreController = Pong::FindGameObject<ScoreController>();
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
