#pragma once

#include "audiomixer.h"
#include "collisionmanager.h"
#include "gameobject.h"
#include "text.h"
#include "timer.h"
#include "uielement.h"
#include "uieventmanager.h"
#include "utils.h"

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

    static void Init(GLFWwindow* window);
    static void GameLoop();
    static void Reset();
    static void Cleanup();

    static void LoadSceneNext(Scene scene);
    static void ExitGame();

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

    template<typename UIType, typename... Args>
    static UIType* AddUIElement(Args&&... args)
    {
        static_assert(std::is_base_of<UIElement, UIType>::value, "UIType must derive from a UIElement");

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

    void LoadScene(Scene scene);

    GLFWwindow* mWindow { nullptr };
    std::vector<std::unique_ptr<GameObject>> mGameObjects {};
    std::vector<std::unique_ptr<UIElement>> mUIElements {};

    CollisionManager mCollisionManager {};
    UIEventManager mUIEventManager {};
    AudioMixer mAudioMixer {};
    Timer mTimer {};

    Scene mNextScene { Scene::TitleScreen };
    bool mChangeSceneRequested { false };
};

} // namespace pong
