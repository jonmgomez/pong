#include "pong.h"

#include "ball.h"
#include "colliderbox.h"
#include "opponent.h"
#include "player.h"

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

    mCheckedCollisions.push_back(std::vector<GameObject*>{});
    mCheckedCollisions.push_back(std::vector<GameObject*>{});
    mCheckedCollisions.push_back(std::vector<GameObject*>{});
}

void Pong::PongGameLoop()
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
    }

    for (auto& collisionVector : mCheckedCollisions)
    {
        collisionVector.reserve(mGameObjects.size());
    }

    for (int i = 0; i < mGameObjects.size(); i++)
    {
        auto& gameObject = mGameObjects[i];
        for (int otherI = 0; otherI < mGameObjects.size(); otherI++)
        {
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

                if (alreadyChecked)
                {
                    if (gameObject->CheckForCollision(*other))
                    {
                        gameObject->OnCollision(*other);
                        other->OnCollision(*gameObject);
                    }
                }

                mCheckedCollisions[otherI].push_back(gameObject.get());
            }
        }
    }

    for (auto& collisionVector : mCheckedCollisions)
    {
        std::cout << "Collision vector size: " << collisionVector.size() << std::endl;
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
