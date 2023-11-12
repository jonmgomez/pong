#pragma once

#include "collisionmanager.h"
#include "gameobject.h"
#include "utils.h"

#include <memory>
#include <vector>

namespace pong
{

class Pong
{
private:
    Pong() = default;
    Pong(const Pong&) = delete;
    Pong& operator=(const Pong&) = delete;
    Pong(Pong&&) = delete;
    Pong& operator=(Pong&&) = delete;
    ~Pong() = default;

    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    CollisionManager mCollisionManager {};

public:
    static Pong& GetInstance();

    static void Init();
    static void GameLoop();
    static void Cleanup();

    template<typename T>
    static T* FindGameObject()
    {
        for (auto& gameObject : GetInstance().mGameObjects)
        {
            auto castedGameObject = dynamic_cast<T*>(gameObject.get());
            if (castedGameObject != nullptr)
            {
                return castedGameObject;
            }
        }
        return nullptr;
    }
};

} // namespace pong
