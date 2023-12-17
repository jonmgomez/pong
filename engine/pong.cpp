#include "pong.h"

#include "ball.h"
#include "colliderbox.h"
#include "config.h"
#include "input.h"
#include "logger.h"
#include "opponent.h"
#include "entity.h"
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
    GetInstance().GetTimer().Init();
    GetInstance().LoadScene(Scene::TitleScreen);
}

void Pong::GameLoop()
{
    Pong::GetInstance().GetTimer().HandleTimerCallbacks();
    Pong::GetInstance().GetCollisionManager().ProcessCollisionsNew(ColliderBox::GetComponents());
    Pong::GetInstance().GetUIEventManager().ProcessEvents(GetInstance().mUIElements);

    if (GetInstance().mChangeSceneRequested)
    {
        GetInstance().LoadScene(GetInstance().mNextScene);
        GetInstance().mChangeSceneRequested = false;
    }

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->OnUpdate();
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
}

void Pong::Cleanup()
{
    Pong::Reset();
    GetInstance().GetAudioMixer().Cleanup();
}

void Pong::LoadSceneNext(Scene scene)
{
    GetInstance().mNextScene = scene;
    GetInstance().mChangeSceneRequested = true;
}

void Pong::LoadScene(Scene scene)
{
    Pong::Reset();

    switch (scene)
    {
        case Scene::TitleScreen:
        {
            auto titleScreen = std::make_unique<TitleScreenController>();
            titleScreen->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(titleScreen));
            break;
        }
        case Scene::Settings:
        {
            auto settingsScreen = std::make_unique<SettingsScreenController>();
            settingsScreen->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(settingsScreen));
            break;
        }
        case Scene::Game:
        {
            constexpr float horizontalWallWidth = 1280 * 2;
            constexpr float horizontalWallHeight = 25;
            constexpr float horizontalWallY = 960;
            constexpr float verticalWallWidth = 25;
            constexpr float verticalWallHeight = 960 * 2;
            constexpr float verticalWallX = 1280;

            auto player = std::make_unique<Player>();
            player->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(player));

            auto opponent = std::make_unique<Opponent>();
            opponent->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(opponent));

            auto ball = std::make_unique<Ball>();
            ball->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(ball));

            auto topWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
            topWall->InitalizeComponents();
            topWall->GetComponent<Transform>()->mPosition = glm::vec3(0.0f, horizontalWallY, 0.0f);
            topWall->SetPosition(glm::vec3(0.0f, horizontalWallY, 0.0f));
            topWall->SetInstanceName("TopWall");
            GetInstance().mGameObjects.push_back(std::move(topWall));

            auto bottomWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
            bottomWall->InitalizeComponents();
            bottomWall->GetComponent<Transform>()->mPosition = glm::vec3(0.0f, -horizontalWallY, 0.0f);
            bottomWall->SetPosition(glm::vec3(0.0f, -horizontalWallY, 0.0f));
            bottomWall->SetInstanceName("BottomWall");
            GetInstance().mGameObjects.push_back(std::move(bottomWall));

            auto playerScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, true);
            playerScoreArea->InitalizeComponents();
            playerScoreArea->GetComponent<Transform>()->mPosition = glm::vec3(verticalWallX, 0.0f, 0.0f);
            playerScoreArea->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
            GetInstance().mGameObjects.push_back(std::move(playerScoreArea));

            auto opponentScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, false);
            opponentScoreArea->InitalizeComponents();
            opponentScoreArea->GetComponent<Transform>()->mPosition = glm::vec3(-verticalWallX, 0.0f, 0.0f);
            opponentScoreArea->SetPosition(glm::vec3(-verticalWallX, 0.0f, 0.0f));
            GetInstance().mGameObjects.push_back(std::move(opponentScoreArea));

            auto scoreController = std::make_unique<ScoreController>();
            scoreController->InitalizeComponents();
            GetInstance().mGameObjects.push_back(std::move(scoreController));
            break;
        }
    }

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->OnStart();
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

void Pong::SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback)
{
    GetInstance().mTimer.AddTimer(gameObjectId, timeout, callback);
}

} // namespace pong
