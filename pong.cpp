#include "pong.h"

#include "ball.h"
#include "colliderbox.h"
#include "opponent.h"
#include "player.h"
#include "wall.h"

namespace pong
{

void Pong::PongInit()
{
    auto player = std::make_unique<Player>();
    player->OnStart();
    mGameObjects.push_back(std::move(player));

    auto opponent = std::make_unique<Opponent>();
    opponent->OnStart();
    mGameObjects.push_back(std::move(opponent));

    auto ball = std::make_unique<Ball>();
    ball->OnStart();
    mGameObjects.push_back(std::move(ball));

    constexpr float horizontalWallWidth = 640 * 2;
    constexpr float horizontalWallHeight = 25;
    constexpr float horizontalWallY = 480;
    constexpr float verticalWallWidth = 25;
    constexpr float verticalWallHeight = 480 * 2;
    constexpr float verticalWallX = 640;

    auto topWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    topWall->OnStart();
    topWall->SetPosition(glm::vec3(0.0f, horizontalWallY, 0.0f));
    mGameObjects.push_back(std::move(topWall));

    auto bottomWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    bottomWall->OnStart();
    bottomWall->SetPosition(glm::vec3(0.0f, -horizontalWallY, 0.0f));
    mGameObjects.push_back(std::move(bottomWall));

    auto leftWall = std::make_unique<Wall>(verticalWallWidth, verticalWallHeight);
    leftWall->OnStart();
    leftWall->SetPosition(glm::vec3(-verticalWallX, 0.0f, 0.0f));
    leftWall->SetInstanceName("WallV");
    mGameObjects.push_back(std::move(leftWall));

    auto rightWall = std::make_unique<Wall>(verticalWallWidth, verticalWallHeight);
    rightWall->OnStart();
    rightWall->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
    rightWall->SetInstanceName("WallV");
    mGameObjects.push_back(std::move(rightWall));
}

void Pong::PongGameLoop()
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
    }

    mCollisionManager.ProcessCollisions(mGameObjects);

    for (auto& gameObject : mGameObjects)
    {
        gameObject->Render();
    }
}

} // namespace pong
