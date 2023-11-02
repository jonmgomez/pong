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

    auto topWall = std::make_unique<Wall>(640.0f * 2, 25.0f);
    topWall->SetPosition(glm::vec3(0.0f, 400.0f, 0.0f));
    mGameObjects.push_back(std::move(topWall));

    auto bottomWall = std::make_unique<Wall>(640.0f * 2, 25.0f);
    bottomWall->SetPosition(glm::vec3(0.0f, -400.0f, 0.0f));
    mGameObjects.push_back(std::move(bottomWall));

    mCurrentCollisions.reserve(mGameObjects.size());
    mCheckedCollisionsNew.reserve(mGameObjects.size());
}

void Pong::PongGameLoop()
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
    }

    CheckForCollisions();

    for (auto& collisionVector : mCheckedCollisions)
    {
        collisionVector.clear();
    }

    for (auto& gameObject : mGameObjects)
    {
        gameObject->Render();
    }
}

bool Pong::IsCheckedCollision(GameObject* firstGameObject, GameObject* secondGameObject) const
{
    for (auto& collisionPair : mCheckedCollisionsNew)
    {
        if (collisionPair.mFirstGameObject == firstGameObject && collisionPair.mSecondGameObject == secondGameObject
         || collisionPair.mFirstGameObject == secondGameObject && collisionPair.mSecondGameObject == firstGameObject)
        {
            return true;
        }
    }
    return false;
}

bool Pong::IsCurrentlyColliding(GameObject* firstGameObject, GameObject* secondGameObject) const
{
    for (auto& collisionPair : mCurrentCollisions)
    {
        if (collisionPair.mFirstGameObject == firstGameObject && collisionPair.mSecondGameObject == secondGameObject
         || collisionPair.mFirstGameObject == secondGameObject && collisionPair.mSecondGameObject == firstGameObject)
        {
            return true;
        }
    }
    return false;
}

void Pong::CheckForCollisions()
{
    for (auto& gameObject : mGameObjects)
    {
        for (auto& otherGameObject : mGameObjects)
        {
            if (gameObject == otherGameObject)
            {
                continue;
            }

            if (!IsCheckedCollision(gameObject.get(), otherGameObject.get()))
            {
                const bool collision = gameObject->CheckForCollision(*otherGameObject);
                const bool wereColliding = IsCurrentlyColliding(gameObject.get(), otherGameObject.get());

                if (collision && !wereColliding)
                {
                    std::cout << "Collision Start!" << std::endl;
                    gameObject->OnCollisionStart(*otherGameObject);
                    otherGameObject->OnCollisionStart(*gameObject);
                    mCurrentCollisions.push_back({ gameObject.get(), otherGameObject.get() });
                }
                else if (collision)
                {
                    std::cout << "Collision Stay!" << std::endl;
                    gameObject->OnCollisionStay(*otherGameObject);
                    otherGameObject->OnCollisionStay(*gameObject);
                }
                else if (wereColliding)
                {
                    std::cout << "Collision End!" << std::endl;
                    gameObject->OnCollisionEnd(*otherGameObject);
                    otherGameObject->OnCollisionEnd(*gameObject);
                    RemoveGameObjectCollisionPair(gameObject.get(), otherGameObject.get());
                }

                mCheckedCollisionsNew.push_back({ gameObject.get(), otherGameObject.get() });
            }
        }
    }

    mCheckedCollisionsNew.clear();
    mCurrentCollisions.clear();
}

void Pong::RemoveGameObjectCollisionPair(GameObject* firstGameObject, GameObject* secondGameObject)
{
    std::cout << "Current Collisions: " << mCurrentCollisions.size() << std::endl;
    mCurrentCollisions.erase(std::remove_if(mCurrentCollisions.begin(), mCurrentCollisions.end(),
        [firstGameObject, secondGameObject](const CollisionPair& collisionPair)
        {
            return collisionPair.mFirstGameObject == firstGameObject && collisionPair.mSecondGameObject == secondGameObject;
        }), mCurrentCollisions.end());
    std::cout << "Current Collisions after: " << mCurrentCollisions.size() << std::endl;
}

} // namespace pong
