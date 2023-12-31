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
    GetInstance().mSceneLoader.PreLoadScenes();
    GetInstance().GetTimer().Init();

    GetInstance().LoadScene(Config::GetValue<std::string>("starting_scene"));
}

void Pong::GameLoop()
{
    Pong& pong = GetInstance();
    pong.GetTimer().HandleTimerCallbacks();
    pong.GetCollisionManager().ProcessCollisions(ColliderBox::GetComponents());
    pong.GetUIEventManager().ProcessEvents();

    if (pong.mChangeSceneRequested)
    {
        pong.LoadScene(pong.mNextScene);
        pong.mChangeSceneRequested = false;
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
    GetInstance().mTimer.Reset();
}

void Pong::Cleanup()
{
    Pong::Reset();
    GetInstance().GetAudioMixer().Cleanup();
}

void Pong::LoadSceneNext(const std::string& sceneName)
{
    GetInstance().mNextScene = sceneName;
    GetInstance().mChangeSceneRequested = true;
}

void Pong::LoadScene(const std::string& sceneName)
{
    Pong::Reset();

    GetInstance().mGameObjects = GetInstance().mSceneLoader.LoadScene(sceneName);

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

} // namespace pong
