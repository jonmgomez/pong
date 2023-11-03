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

    const float horizontalWallWidth = 640 * 2;
    const float horizontalWallHeight = 25;
    const float horizontalWallY = 480;
    const float verticalWallWidth = 25;
    const float verticalWallHeight = 480 * 2;
    const float verticalWallX = 640;

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
    leftWall->SetName("WallV");
    mGameObjects.push_back(std::move(leftWall));

    auto rightWall = std::make_unique<Wall>(verticalWallWidth, verticalWallHeight);
    rightWall->OnStart();
    rightWall->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
    rightWall->SetName("WallV");
    mGameObjects.push_back(std::move(rightWall));

    mCurrentCollisions.reserve(mGameObjects.size());
}

void Pong::PongGameLoop()
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
    }

    CheckForCollisions();

    for (auto& gameObject : mGameObjects)
    {
        gameObject->Render();
    }
}

void Pong::CheckForCollisions()
{
    for (int index = 0; index < mGameObjects.size(); index++)
    {
        auto& gameObject = mGameObjects[index];
        for (int otherIndex = index + 1; otherIndex < mGameObjects.size(); otherIndex++)
        {
            auto& otherGameObject = mGameObjects[otherIndex];

            const bool collision = gameObject->CheckForCollision(*otherGameObject);
            const bool wereColliding = IsCurrentlyColliding(gameObject->GetId(), otherGameObject->GetId());

            if (collision && !wereColliding)
            {
                gameObject->OnCollisionStart(*otherGameObject);
                otherGameObject->OnCollisionStart(*gameObject);
                mCurrentCollisions.push_back({ gameObject->GetId(), otherGameObject->GetId() });
            }
            else if (collision)
            {
                gameObject->OnCollisionStay(*otherGameObject);
                otherGameObject->OnCollisionStay(*gameObject);
            }
            else if (wereColliding)
            {
                gameObject->OnCollisionStop(*otherGameObject);
                otherGameObject->OnCollisionStop(*gameObject);
                RemoveGameObjectCollisionPair(gameObject->GetId(), otherGameObject->GetId());
            }
        }
    }
}

bool Pong::IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const
{
    for (auto& collisionPair : mCurrentCollisions)
    {
        if (IsCollisionPairValid(collisionPair, firstGameObjectId, secondGameObjectId))
        {
            return true;
        }
    }
    return false;
}

bool Pong::IsCollisionPairValid(const CollisionPair& pair, int firstGameObjectId, int secondGameObjectId) const
{
    return pair.mFirstGameObjectId == firstGameObjectId && pair.mSecondGameObjectId == secondGameObjectId
        || pair.mFirstGameObjectId == secondGameObjectId && pair.mSecondGameObjectId == firstGameObjectId;
}

void Pong::RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId)
{
    mCurrentCollisions.erase(std::remove_if(mCurrentCollisions.begin(), mCurrentCollisions.end(),
        [&](const CollisionPair& collisionPair){ return IsCollisionPairValid(collisionPair, firstGameObjectId, secondGameObjectId); }),
        mCurrentCollisions.end());
}

} // namespace pong
