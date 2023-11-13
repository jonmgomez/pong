#pragma once

#include "collisionmanager.h"
#include "gameobject.h"
#include "timer.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <vector>
#include <functional>

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

    CollisionManager& GetCollisionManager();
    Timer& GetTimer();

    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    CollisionManager mCollisionManager {};
    Timer mTimer {};
    bool mFirstFrame { true };

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

    static void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);
};

} // namespace pong
