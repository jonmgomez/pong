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
    mMesh = std::make_unique<Rectangle>(width, height);
    mColliderBox = std::make_unique<ColliderBox>(width, height);
    mIsPlayerScoreArea = playerSide;
    SetInstanceName("ScoreArea");
}

void ScoreArea::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "Ball")
    {
        auto scoreController = Pong::FindGameObject<ScoreController>();

        if (scoreController == nullptr)
        {
            spdlog::error("ScoreController not found!");
            return;
        }

        if (mIsPlayerScoreArea)
        {
            spdlog::info("Player scored!");
            scoreController->PlayerScored();
        }
        else
        {
            spdlog::info("Opponent scored!");
            scoreController->OpponentScored();
        }

        spdlog::info("New Score: P {} - O {}", scoreController->GetPlayerScore(), scoreController->GetOpponentScore());
    }
}

} // namespace pong
