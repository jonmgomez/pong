#include "pong.h"

#include "ball.h"
#include "colliderbox.h"
#include "config.h"
#include "logger.h"
#include "opponent.h"
#include "player.h"
#include "scorearea.h"
#include "scorecontroller.h"
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

UIEventManager& Pong::GetUIEventManager()
{
    return mUIEventManager;
}

Timer& Pong::GetTimer()
{
    return mTimer;
}

void Pong::Init(GLFWwindow* window)
{
    GetInstance().mWindow = window;
    GetInstance().LoadScene(Scene::TitleScreen);
}

void Pong::GameLoop()
{
    Pong::GetInstance().GetTimer().HandleTimerCallbacks();
    Pong::GetInstance().GetCollisionManager().ProcessCollisions(GetInstance().mGameObjects);
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

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->Render();
    }

    for (auto& uiElements : GetInstance().mUIElements)
    {
        uiElements->Render();
    }
}

void Pong::Cleanup()
{
    GetInstance().mGameObjects.clear();
    GetInstance().mUIElements.clear();
}

void Pong::LoadSceneNext(Scene scene)
{
    GetInstance().mNextScene = scene;
    GetInstance().mChangeSceneRequested = true;
}

void Pong::LoadScene(Scene scene)
{
    Pong::Cleanup();

    switch (scene)
    {
        case Scene::TitleScreen:
        {
            auto titleScreen = std::make_unique<TitleScreenController>();
            GetInstance().mGameObjects.push_back(std::move(titleScreen));
            break;
        }
        case Scene::Settings:
        {
            break;
        }
        case Scene::Game:
        {
            auto player = std::make_unique<Player>();
            GetInstance().mGameObjects.push_back(std::move(player));

            auto opponent = std::make_unique<Opponent>();
            GetInstance().mGameObjects.push_back(std::move(opponent));

            auto ball = std::make_unique<Ball>();
            GetInstance().mGameObjects.push_back(std::move(ball));

            constexpr float horizontalWallWidth = 1280 * 2;
            constexpr float horizontalWallHeight = 25;
            constexpr float horizontalWallY = 960;
            constexpr float verticalWallWidth = 25;
            constexpr float verticalWallHeight = 960 * 2;
            constexpr float verticalWallX = 1280;

            auto topWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
            topWall->SetPosition(glm::vec3(0.0f, horizontalWallY, 0.0f));
            topWall->SetInstanceName("TopWall");
            GetInstance().mGameObjects.push_back(std::move(topWall));

            auto bottomWall = std::make_unique<Wall>(horizontalWallWidth, horizontalWallHeight);
            bottomWall->SetPosition(glm::vec3(0.0f, -horizontalWallY, 0.0f));
            bottomWall->SetInstanceName("BottomWall");
            GetInstance().mGameObjects.push_back(std::move(bottomWall));

            auto playerScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, true);
            playerScoreArea->SetPosition(glm::vec3(verticalWallX, 0.0f, 0.0f));
            GetInstance().mGameObjects.push_back(std::move(playerScoreArea));

            auto opponentScoreArea = std::make_unique<ScoreArea>(verticalWallWidth, verticalWallHeight, false);
            opponentScoreArea->SetPosition(glm::vec3(-verticalWallX, 0.0f, 0.0f));
            GetInstance().mGameObjects.push_back(std::move(opponentScoreArea));

            auto scoreController = std::make_unique<ScoreController>();
            GetInstance().mGameObjects.push_back(std::move(scoreController));
            break;
        }
    }

    for (auto& gameObject : GetInstance().mGameObjects)
    {
        gameObject->OnStart();
    }
}

void Pong::ExitGame()
{
    glfwSetWindowShouldClose(GetInstance().mWindow, GLFW_TRUE);
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

Text* Pong::AddText(const std::string& text, const std::string& fontPath,
                    float scale, int pixelLineHeight,
                    const glm::vec3& position)
{
    auto newText = std::make_unique<Text>(text, fontPath, scale, pixelLineHeight);
    Text* textPtr = newText.get();

    newText->SetPosition(position);
    GetInstance().mUIElements.push_back(std::move(newText));
    return textPtr;
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
