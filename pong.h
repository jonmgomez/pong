#pragma once

#include "collisionmanager.h"
#include "gameobject.h"

#include <algorithm>
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

    std::vector<std::shared_ptr<GameObject>>mGameObjects {};
    CollisionManager mCollisionManager {};

public:
    static Pong& GetInstance();

    static void PongInit();
    static void PongGameLoop();
    static void PongCleanup();

    template<typename T>
    static std::shared_ptr<T> FindGameObject()
    {
        for (auto& gameObject : GetInstance().mGameObjects)
        {
            auto castedGameObject = std::dynamic_pointer_cast<T>(gameObject);
            if (castedGameObject != nullptr)
            {
                return castedGameObject;
            }
        }
        return nullptr;
    }

    template<typename T>
    static bool GameObjectExists(const T& gameObject)
    {
        return std::any_of(std::begin(GetInstance().mGameObjects), std::end(GetInstance().mGameObjects),
            [&](const std::unique_ptr<GameObject>& currentGameObject) { return currentGameObject.get() == &gameObject; });
    }
};

} // namespace pong
