#pragma once

#include "audiomixer.h"
#include "collisionmanager.h"
#include "component.h"
#include "gameobject.h"
#include "text.h"
#include "timer.h"
#include "transform.h"
#include "uielement.h"
#include "uieventmanager.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <vector>
#include <functional>

namespace pong
{

enum class SceneType
{
    Title,
    Settings,
    Game
};

class Pong
{
public:
    static Pong& GetInstance();

    static void Init();
    static void GameLoop();
    static void Reset();
    static void Cleanup();

    static void LoadSceneNext(SceneType scene);

    // Returns the first component of type T found in the scene
    template<typename T, typename... Args>
    static T* FindComponentOfType()
    {
        const std::vector<std::unique_ptr<T>>& components = T::GetComponents();

        if (components.empty())
        {
            return nullptr;
        }

        return components[0].get();
    }

    // Returns the first component of type T found in the scene
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Behavior, T>>, typename... Args>
    static T* FindComponentOfBehavior()
    {
        std::vector<std::unique_ptr<Behavior>>& behaviors = Behavior::GetComponents();

        for (auto& behavior : behaviors)
        {
            if (static_cast<std::unique_ptr<BehaviorIDGenerator>>(behavior)::GetBehaviorID() == T::GetBehaviorID())
            {
                return static_cast<T*>(component.get());
            }
        }

        return static_cast<T>(behaviors[0].get());
    }

    static GameObject* FindGameObjectByName(const std::string& name);

    template<typename UIType, typename = std::enable_if_t<std::is_base_of_v<UIElement, UIType>>, typename... Args>
    static UIType* AddUIElement(Args&&... args)
    {
        auto newUIElement = std::make_unique<UIType>(std::forward<Args>(args)...);
        UIType* uiElementPtr = newUIElement.get();

        GetInstance().mUIElements.push_back(std::move(newUIElement));
        Pong::UpdateUIElementOrderLayer();
        return uiElementPtr;
    }

    static void UpdateUIElementOrderLayer();

    static void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);

    CollisionManager& GetCollisionManager();
    UIEventManager& GetUIEventManager();
    AudioMixer& GetAudioMixer();
    Timer& GetTimer();

private:
    Pong() = default;
    Pong(const Pong&) = delete;
    Pong& operator=(const Pong&) = delete;
    Pong(Pong&&) = delete;
    Pong& operator=(Pong&&) = delete;
    ~Pong() = default;

    void LoadScene(SceneType scene);

    std::vector<std::unique_ptr<GameObject>> mGameObjects {};
    std::vector<std::unique_ptr<UIElement>> mUIElements {};

    CollisionManager mCollisionManager {};
    UIEventManager mUIEventManager {};
    AudioMixer mAudioMixer {};
    Timer mTimer {};

    SceneType mNextScene { SceneType::Title };
    bool mChangeSceneRequested { false };
};

} // namespace pong
