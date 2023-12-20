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
    GetInstance().LoadScene(SceneType::Game);
}

void Pong::GameLoop()
{
    Pong::GetInstance().GetTimer().HandleTimerCallbacks();
    Pong::GetInstance().GetCollisionManager().ProcessCollisions(ColliderBox::GetComponents());
    Pong::GetInstance().GetUIEventManager().ProcessEvents(GetInstance().mUIElements);

    if (GetInstance().mChangeSceneRequested)
    {
        GetInstance().LoadScene(GetInstance().mNextScene);
        GetInstance().mChangeSceneRequested = false;
    }

    for (auto& behavior : Behavior::GetComponents())
    {
        behavior->OnUpdate();
    }

    Renderer::DrawAllMeshes(Mesh::GetComponents());

    for (auto& uiElements : GetInstance().mUIElements)
    {
        uiElements->Render();
    }

    // Done last because input callbacks are done in glfwPollEvents after this loop.
    // So this effectively keeps the values from the new frame before updated from pressed -> held
    Input::Update();
}

void Pong::Reset()
{
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

    switch (sceneType)
    {
        case SceneType::Title:
        {
            break;
        }
        case SceneType::Settings:
        {
            break;
        }
        case SceneType::Game:
        {
            GameScene scene;
            scene.BuildScene();
            GetInstance().mGameObjects = scene.TransferGameObjects();
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
