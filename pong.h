#pragma once

#include "collisionmanager.h"
#include "gameobject.h"

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

    static void PongInit();
    static void PongGameLoop();
    static void PongCleanup();

    template<typename T>
    static T* FindGameObject()
    {
        for (auto& gameObject : GetInstance().mGameObjects)
        {
            T* castedGameObject = dynamic_cast<T*>(gameObject.get());
            if (castedGameObject != nullptr)
            {
                return castedGameObject;
            }
        }

        return nullptr;
    }
};

} // namespace pong
