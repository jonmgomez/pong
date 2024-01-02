#pragma once

#include "audiomixer.h"
#include "collisionmanager.h"
#include "component.h"
#include "componentmanager.h"
#include "fontbank.h"
#include "gameobject.h"
#include "sceneloader.h"
#include "text.h"
#include "timer.h"
#include "transform.h"
#include "uicomponent.h"
#include "uieventmanager.h"
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
    static void Reset();
    static void Cleanup();

    static void LoadSceneNext(const std::string& sceneName);

    // Returns the first component of type T found in the scene
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseComponent, T> && !std::is_base_of_v<Behavior, T>>>
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
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Behavior, T>>, typename = void>
    static T* FindComponentOfType()
    {
        // Since behaviors are the only components meant to be overridden, they are stored in a Behavior vector
        // getting a specific behavior class from the vector is done by comparing the behavior Id
        const std::vector<std::unique_ptr<Behavior>>& behaviors = Behavior::GetComponents();

        for (auto& behavior : behaviors)
        {
            if (behavior->GetBehaviorId() == GetIdFromBehavior<T>())
            {
                return static_cast<T*>(behavior.get());
            }
        }

        return nullptr;
    }

    static GameObject* FindGameObjectByName(const std::string& name);

    CollisionManager& GetCollisionManager();
    ComponentManager& GetComponentManager();
    UIEventManager& GetUIEventManager();
    AudioMixer& GetAudioMixer();
    FontBank& GetFontBank();
    Timer& GetTimer();

private:
    Pong() = default;
    Pong(const Pong&) = delete;
    Pong& operator=(const Pong&) = delete;
    Pong(Pong&&) = delete;
    Pong& operator=(Pong&&) = delete;
    ~Pong() = default;

    void LoadScene(const std::string& sceneName);

    std::vector<std::unique_ptr<GameObject>> mGameObjects {};

    CollisionManager mCollisionManager {};
    ComponentManager mComponentManager {};
    UIEventManager mUIEventManager {};
    SceneLoader mSceneLoader {};
    AudioMixer mAudioMixer {};
    FontBank mFontBank {};
    Timer mTimer {};

    std::string mNextScene { "Title" };
    bool mChangeSceneRequested { false };
};

} // namespace pong
