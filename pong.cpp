#include "pong.h"

#include "ball.h"
#include "colliderbox.h"
#include "opponent.h"
#include "player.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "wall.h"

namespace pong
{

Pong& Pong::GetInstance()
{
    static Pong instance;
    return instance;
}

void Pong::PongInit()
{
    auto player = std::make_shared<Player>();
    GetInstance().mGameObjects.push_back(player);

    auto opponent = std::make_shared<Opponent>();
    GetInstance().mGameObjects.push_back(opponent);

    auto ball = std::make_shared<Ball>();
    GetInstance().mGameObjects.push_back(ball);

    constexpr float horizontalWallWidth = 640 * 2;
    constexpr float horizontalWallHeight = 25;
    constexpr float horizontalWallY = 480;
    constexpr float verticalWallWidth = 25;
    constexpr float verticalWallHeight = 480 * 2;
    constexpr float verticalWallX = 640;

    auto topWall = std::make_shared<Wall>(horizontalWallWidth, horizontalWallHeight);
    GetInstance().mGameObjects.push_back(topWall);

    auto bottomWall = std::make_shared<Wall>(horizontalWallWidth, horizontalWallHeight);
    GetInstance().mGameObjects.push_back(bottomWall);

    auto playerScoreArea = std::make_shared<ScoreArea>(verticalWallWidth, verticalWallHeight, true);
    GetInstance().mGameObjects.push_back(playerScoreArea);

    auto opponentScoreArea = std::make_shared<ScoreArea>(verticalWallWidth, verticalWallHeight, false);
    GetInstance().mGameObjects.push_back(opponentScoreArea);

    auto scoreController = std::make_shared<ScoreController>();
    GetInstance().mGameObjects.push_back(scoreController);

    player->OnStart();
    opponent->OnStart();
    ball->OnStart();
    topWall->OnStart();
    topWall->SetPosition(glm::vec3(0.0f, horizontalWallY, 0.0f));
    bottomWall->OnStart();
    bottomWall->SetPosition(glm::vec3(0.0f, -horizontalWallY, 0.0f));
    playerScoreArea->OnStart();
    playerScoreArea->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
    opponentScoreArea->OnStart();
    opponentScoreArea->SetPosition(glm::vec3(-verticalWallX, 0.0f, 0.0f));
    scoreController->OnStart();

}

void Pong::PongGameLoop()
{
    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->OnUpdate();
    }

    GetInstance().mCollisionManager.ProcessCollisions(GetInstance().mGameObjects);

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->Render();
    }
}

void Pong::PongCleanup()
{
    GetInstance().mGameObjects.clear();
}

} // namespace pong
