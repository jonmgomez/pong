#include "pong.h"

#include "behavior.h"
#include "colliderbox.h"
#include "config.h"
#include "input.h"
#include "logger.h"

namespace pong
{

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

FontBank& Pong::GetFontBank()
{
    return mFontBank;
}

Timer& Pong::GetTimer()
{
    return mTimer;
}

void Pong::Init()
{
    timer::SetTimerInstance(&mTimer);
    globals::audio::SetAudioMixerInstance(&mAudioMixer);

    GetAudioMixer().Init();
    mFontBank.LoadFonts();
    mSceneLoader.PreLoadScenes();
    GetTimer().Init();

    LoadScene(Config::GetValue<std::string>("starting_scene", "Title"));
}

void Pong::GameLoop()
{
    GetTimer().HandleTimerCallbacks();
    GetCollisionManager().ProcessCollisions(ColliderBox::GetComponents());
    GetUIEventManager().ProcessEvents();

    if (mChangeSceneRequested)
    {
        LoadScene(mNextScene);
        mChangeSceneRequested = false;
    }

    for (auto& behavior : Behavior::GetComponents())
    {
        behavior->OnUpdate();
    }
}

void Pong::Reset()
{
    mComponentManager.Reset();

    for (auto& gameobject : mGameObjects)
    {
        if (gameobject->ShouldDestroyOnLoad())
        {
            gameobject->Destroy();
        }
    }

    mGameObjects.erase(std::remove_if(mGameObjects.begin(), mGameObjects.end(), [] (const auto& gameObject)
    {
        return gameObject->ShouldDestroyOnLoad();
    }), mGameObjects.end());

    mAudioMixer.Reset();
    mTimer.Reset();
}

void Pong::Cleanup()
{
    Pong::Reset();
    GetAudioMixer().Cleanup();
}

void Pong::LoadSceneNext(const std::string& sceneName)
{
    mNextScene = sceneName;
    mChangeSceneRequested = true;
}

void Pong::LoadScene(const std::string& sceneName)
{
    Pong::Reset();

    GameObjectCollection gameObjects = mSceneLoader.LoadScene(sceneName);
    for (auto& gameObject : gameObjects)
    {
        mGameObjects.push_back(std::move(gameObject));
    }

    for (auto& behavior : Behavior::GetComponents())
    {
        if (!behavior->mOnStartCalled)
        {
            behavior->OnStart();
            behavior->mOnStartCalled = true;
        }
    }
}

GameObject* Pong::FindGameObjectByName(const std::string& name)
{
    auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(), [&name] (const auto& gameObject)
    {
        return gameObject->GetInstanceName() == name;
    });

    if (it != mGameObjects.end())
    {
        return it->get();
    }

    return nullptr;
}

} // namespace pong

namespace pong::globals::game
{

Pong* gPong { nullptr };

Pong* GetPongInstance()
{
    return gPong;
}

void SetPongInstance(Pong* pong)
{
    gPong = pong;
}

GameObject* FindGameObjectByName(const std::string& name)
{
    return GetPongInstance()->FindGameObjectByName(name);
}

void LoadSceneNext(const std::string& sceneName)
{
    GetPongInstance()->LoadSceneNext(sceneName);
}

} // namespace pong::globals::game
