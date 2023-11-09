#include "scorearea.h"

#include "colliderbox.h"
#include "pong.h"
#include "rectangle.h"
#include "scorecontroller.h"

#include <spdlog/spdlog.h>

namespace pong
{

ScoreArea::ScoreArea(float width, float height, bool playerSide)
{
    mColliderBox = std::make_unique<ColliderBox>(width, height);
    mIsPlayerScoreArea = playerSide;
    SetInstanceName("ScoreArea");
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
            spdlog::info("Player scored!");
            mScoreController->PlayerScored();
        }
        else
        {
            spdlog::info("Opponent scored!");
            mScoreController->OpponentScored();
        }

        spdlog::info("New Score: P {} - O {}", mScoreController->GetPlayerScore(), mScoreController->GetOpponentScore());
    }
}

} // namespace pong
