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

    for (int i = 0; i < mGameObjects.size(); i++)
    {
        mCheckedCollisions.push_back(std::vector<GameObject*>());
        mCheckedCollisions[i].reserve(mGameObjects.size());

        mCurrentlyColliding.push_back(std::vector<GameObject*>());
        mCurrentlyColliding[i].reserve(mGameObjects.size());
    }
}

void Pong::PongGameLoop()
{
    std::cout << "PongGameLoop" << std::endl;
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
    }

    for (int i = 0; i < mGameObjects.size(); i++)
    {
        auto& gameObject = mGameObjects[i];
        for (int otherI = 0; otherI < mGameObjects.size(); otherI++)
        {
            std::cout << "Checking " << gameObject->GetName() << " and " << mGameObjects[otherI]->GetName() << std::endl;
            auto& other = mGameObjects[otherI];
            if (gameObject.get() != other.get())
            {
                bool alreadyChecked = false;
                for (GameObject* alreadyCollided : mCheckedCollisions[i])
                {
                    if (alreadyCollided == other.get())
                    {
                        alreadyChecked = true;
                        break;
                    }
                }

                if (!alreadyChecked)
                {
                    if (gameObject->CheckForCollision(*other))
                    {
                        std::cout << "Collision!" << std::endl;
                        bool alreadyCollided = false;
                        for (GameObject* currentCollider : mCurrentlyColliding[i])
                        {
                            if (currentCollider == other.get())
                            {
                                std::cout << "Already collided would call Stay()" << std::endl;
                                alreadyCollided = true;
                                // gameobject->OnCollisionStay();
                                // other->OnCollisionStay();
                                break;
                            }
                        }

                        if (!alreadyCollided)
                        {
                            gameObject->OnCollision(*other);
                            other->OnCollision(*gameObject);
                            mCurrentlyColliding[i].push_back(other.get());
                            mCurrentlyColliding[otherI].push_back(gameObject.get());
                        }

                        // Only add this object as checked because the other object can be
                        // encompassed in this object's collider box. If the encompassed collider
                        // checks the other's positions it would appear as not colliding.
                        mCheckedCollisions[otherI].push_back(gameObject.get());
                    }
                    else
                    {
                        GameObject* previouslyCollided = nullptr;
                        for (GameObject* currentCollider : mCurrentlyColliding[i])
                        {
                            if (currentCollider == other.get())
                            {
                                previouslyCollided = currentCollider;
                                break;
                            }
                        }

                        if (previouslyCollided != nullptr)
                        {
                            mCurrentlyColliding[i].erase(
                                std::remove(mCurrentlyColliding[i].begin(),
                                            mCurrentlyColliding[i].end(),
                                            previouslyCollided),
                                mCurrentlyColliding[i].end());
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto& collisionVector : mCheckedCollisions)
    {
        collisionVector.clear();
    }

    for (auto& gameObject : mGameObjects)
    {
        gameObject->Render();
    }
}

} // namespace pong
