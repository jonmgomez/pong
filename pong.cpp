#include "pong.h"

#include "ball.h"
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

    const float horizontalWallWidth = 640 * 2;
    const float horizontalWallHeight = 25;
    const float horizontalWallY = 480;
    const float verticalWallWidth = 25;
    const float verticalWallHeight = 480 * 2;
    const float verticalWallX = 640;

    auto topWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    topWall->OnStart();
    topWall->mPosition = glm::vec3(0.0f, horizontalWallY, 0.0f);
    mGameObjects.push_back(std::move(topWall));

    auto bottomWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
    bottomWall->OnStart();
    bottomWall->mPosition = glm::vec3(0.0f, -horizontalWallY, 0.0f);
    mGameObjects.push_back(std::move(bottomWall));

    auto leftWall = std::make_unique<Wall>(verticalWallWidth, verticalWallHeight);
    leftWall->OnStart();
    leftWall->mPosition = glm::vec3(-verticalWallX, 0.0f, 0.0f);
    mGameObjects.push_back(std::move(leftWall));

    auto rightWall = std::make_unique<Wall>(verticalWallWidth, verticalWallHeight);
    rightWall->OnStart();
    rightWall->mPosition = glm::vec3(verticalWallX, 0.0f, 0.0f);
    mGameObjects.push_back(std::move(rightWall));
}

void Pong::PongGameLoop()
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
        gameObject->Render();
    }
}

} // namespace pong
