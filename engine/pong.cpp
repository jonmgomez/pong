#include "pong.h"

#include "ball.h"
#include "behavior.h"
#include "colliderbox.h"
#include "config.h"
#include "input.h"
#include "logger.h"
#include "opponent.h"
#include "player.h"
#include "renderer.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "settingsscreencontroller.h"
#include "titlescreencontroller.h"
#include "wall.h"
#include "pongscenes.h"

namespace pong
{

Pong& Pong::GetInstance()
{
    static Pong instance;
    return instance;
}

CollisionManager& Pong::GetCollisionManager()
{
    return mCollisionManager;
}

ComponentManager& Pong::GetComponentManager()
{
    return mComponentManager;
}

UIEventManager& Pong::GetUIEventManager()
{
    return mUIEventManager;
}

AudioMixer& Pong::GetAudioMixer()
{
    return mAudioMixer;
}

Timer& Pong::GetTimer()
{
    return mTimer;
}

void Pong::Init()
{
    GetInstance().GetAudioMixer().Init();
    GetInstance().GetTimer().Init();
    GetInstance().LoadScene(SceneType::Title);
}

void Pong::GameLoop()
{
    Pong::GetInstance().GetTimer().HandleTimerCallbacks();
    Pong::GetInstance().GetCollisionManager().ProcessCollisions(ColliderBox::GetComponents());
    Pong::GetInstance().GetUIEventManager().ProcessEvents();

    if (GetInstance().mChangeSceneRequested)
    {
        GetInstance().LoadScene(GetInstance().mNextScene);
        GetInstance().mChangeSceneRequested = false;
    }

    for (auto& behavior : Behavior::GetComponents())
    {
        behavior->OnUpdate();
    }

    Renderer::DrawAll();

    // Done last because input callbacks are done in glfwPollEvents after this loop.
    // So this effectively keeps the values from the new frame before updated from pressed -> held
    Input::Update();
}

void Pong::Reset()
{
    for (auto& gameobject : GetInstance().mGameObjects)
    {
        gameobject->Destroy();
    }

    GetInstance().mComponentManager.Reset();
    GetInstance().mGameObjects.clear();
    GetInstance().mUIElements.clear();
    GetInstance().mTimer.Reset();
}

void Pong::Cleanup()
{
    Pong::Reset();
    GetInstance().GetAudioMixer().Cleanup();
}

void Pong::LoadSceneNext(SceneType sceneType)
{
    GetInstance().mNextScene = sceneType;
    GetInstance().mChangeSceneRequested = true;
}

void Pong::LoadScene(SceneType sceneType)
{
    Pong::Reset();

    const auto LoadSceneObjects = [&](auto scene) {
        scene.BuildScene();
        GetInstance().mGameObjects = scene.TransferGameObjects();
    };

    switch (sceneType)
    {
        case SceneType::Title:
        {
            LoadSceneObjects(TitleScene());
            break;
        }
        case SceneType::Settings:
        {
            LoadSceneObjects(SettingScene());
            break;
        }
        case SceneType::Game:
        {
            LoadSceneObjects(GameScene());
            break;
        }
    }

    for (auto& behavior : Behavior::GetComponents())
    {
        behavior->OnStart();
    }
}

GameObject* Pong::FindGameObjectByName(const std::string& name)
{
    auto it = std::find_if(GetInstance().mGameObjects.begin(), GetInstance().mGameObjects.end(), [&name] (const auto& gameObject)
    {
        return gameObject->GetInstanceName() == name;
    });

    if (it != GetInstance().mGameObjects.end())
    {
        return it->get();
    }

    return nullptr;
}

void Pong::UpdateUIElementOrderLayer()
{
    std::sort(GetInstance().mUIElements.begin(), GetInstance().mUIElements.end(), [] (const auto& lhs, const auto& rhs)
    {
        return lhs->GetOrderLayer() < rhs->GetOrderLayer();
    });
}

} // namespace pong
