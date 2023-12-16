#pragma once

#include "audiomixer.h"
#include "collisionmanager.h"
#include "component.h"
#include "componentmanager.h"
#include "gameobject.h"
#include "text.h"
#include "timer.h"
#include "uielement.h"
#include "uieventmanager.h"
#include "utils.h"

#include "transform.h"

#include <chrono>
#include <memory>
#include <vector>
#include <functional>

namespace pong
{

enum class Scene
{
    TitleScreen,
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

    static void LoadSceneNext(Scene scene);

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

    template<typename UIType, typename = std::enable_if_t<std::is_base_of_v<UIElement, UIType>>, typename... Args>
    static UIType* AddUIElement(Args&&... args)
    {
        auto newUIElement = std::make_unique<UIType>(std::forward<Args>(args)...);
        UIType* uiElementPtr = newUIElement.get();

        GetInstance().mUIElements.push_back(std::move(newUIElement));
        Pong::UpdateUIElementOrderLayer();
        return uiElementPtr;
    }

    template<typename ComponentSubType, typename... Args>
    static void AddComponent(Args&&... args)
    {
        auto newComponent = std::make_unique<ComponentSubType>(std::forward<Args>(args)...);
        GetInstance().mComponentManager.AddComponent<ComponentSubType>(newComponent);
    }

    static void UpdateUIElementOrderLayer();

    static void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);

    CollisionManager& GetCollisionManager();
    ComponentManager& GetComponentManager();
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

    void LoadScene(Scene scene);

    std::vector<std::unique_ptr<GameObject>> mGameObjects {};
    std::vector<std::unique_ptr<UIElement>> mUIElements {};

    std::vector<std::unique_ptr<ColliderBox>> mCompColliderBoxes {};
    std::vector<std::unique_ptr<Transform>> mCompTransforms {};
    //std::vector<std::unique_ptr<Mesh>> mCompMeshes {};

    CollisionManager mCollisionManager {};
    ComponentManager mComponentManager {};
    UIEventManager mUIEventManager {};
    AudioMixer mAudioMixer {};
    Timer mTimer {};

    Scene mNextScene { Scene::TitleScreen };
    bool mChangeSceneRequested { false };
};

} // namespace pong
