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

void Pong::Init()
{
    auto player = std::make_unique<Player>();
    GetInstance().mGameObjects.push_back(std::move(player));

    auto opponent = std::make_unique<Opponent>();
    GetInstance().mGameObjects.push_back(std::move(opponent));

    auto ball = std::make_unique<Ball>();
    GetInstance().mGameObjects.push_back(std::move(ball));

    constexpr float horizontalWallWidth = 640 * 2;
    constexpr float horizontalWallHeight = 25;
    constexpr float horizontalWallY = 480;
    constexpr float verticalWallWidth = 25;
    constexpr float verticalWallHeight = 480 * 2;
    constexpr float verticalWallX = 640;

    auto topWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    topWall->SetPosition(glm::vec3(0.0f, horizontalWallY, 0.0f));
    GetInstance().mGameObjects.push_back(std::move(topWall));

    auto bottomWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    bottomWall->SetPosition(glm::vec3(0.0f, -horizontalWallY, 0.0f));
    GetInstance().mGameObjects.push_back(std::move(bottomWall));

    auto playerScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, true);
    playerScoreArea->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
    GetInstance().mGameObjects.push_back(std::move(playerScoreArea));

    auto opponentScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, false);
    opponentScoreArea->SetPosition(glm::vec3(-verticalWallX, 0.0f, 0.0f));
    GetInstance().mGameObjects.push_back(std::move(opponentScoreArea));

    auto scoreController = std::make_unique<ScoreController>();
    GetInstance().mGameObjects.push_back(std::move(scoreController));

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->OnStart();
    }
}

void Pong::GameLoop()
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

void Pong::Cleanup()
{
    GetInstance().mGameObjects.clear();
}

} // namespace pong
