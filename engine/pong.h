#pragma once

#include "collisionmanager.h"
#include "gameobject.h"
#include "text.h"
#include "timer.h"
#include "uielement.h"
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

    static Text* AddText(const std::string& text, const std::string& fontPath,
                         float scale, int pixelLineHeight = 128,
                         const glm::vec3& position = glm::vec3(0.0f));

    template<typename MeshType, typename... Args>
    static MeshType* AddUIElement(Args&&... args)
    {
        auto newUIElement = std::make_unique<MeshType>(std::forward<Args>(args)...);
        auto uiElementPtr = newUIElement.get();

        GetInstance().mUIElements.push_back(std::move(newUIElement));
        return uiElementPtr;
    }

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
    std::vector<std::unique_ptr<UIElement>> mUIElements {};

    CollisionManager mCollisionManager {};
    Timer mTimer {};
    bool mFirstFrame { true };
};

} // namespace pong
