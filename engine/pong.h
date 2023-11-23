#pragma once

#include "collisionmanager.h"
#include "gameobject.h"
#include "text.h"
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

    static GameObject* FindGameObjectByName(const std::string& name);

    static void AddGameObject(std::unique_ptr<GameObject> gameObject);

    static void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);

private:
    Pong() = default;
    Pong(const Pong&) = delete;
    Pong& operator=(const Pong&) = delete;
    Pong(Pong&&) = delete;
    Pong& operator=(Pong&&) = delete;
    ~Pong() = default;

    CollisionManager& GetCollisionManager();
    Timer& GetTimer();

    std::vector<std::unique_ptr<GameObject>> mGameObjects {};
    std::vector<std::unique_ptr<Text>> mTexts {};

    CollisionManager mCollisionManager {};
    Timer mTimer {};
    bool mFirstFrame { true };
};

} // namespace pong
