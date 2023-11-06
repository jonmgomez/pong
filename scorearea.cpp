#include "scorearea.h"

#include "colliderbox.h"
#include "pong.h"
#include "rectangle.h"
#include "scorecontroller.h"

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
            std::cout << "ScoreController not found!" << std::endl;
            return;
        }

        if (mIsPlayerScoreArea)
        {
            std::cout << "Player scored!" << std::endl;
            scoreController->PlayerScored();
        }
        else
        {
            std::cout << "Opponent scored!" << std::endl;
            scoreController->OpponentScored();
        }

        std::cout << "---- New Score ----\n";
        std::cout << "Player: " << scoreController->GetPlayerScore() << "\n";
        std::cout << "Opponent: " << scoreController->GetOpponentScore() << std::endl;
    }
}

} // namespace pong
