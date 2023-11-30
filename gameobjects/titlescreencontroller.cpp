#include "titlescreencontroller.h"

#include "logger.h"
#include "config.h"
#include "pong.h"

namespace pong
{

void TitleScreenController::OnStart()
{
    LogInfo("TitleScreenController::OnStart");
    mPongText = Pong::AddText("Pong", Config::GetValue<std::string>("font"), 1.0f, 350);
    mPongText->SetPosition(glm::vec3(0.0f, 750.0f, 0.0f));

    mPlayText = Pong::AddUIElement<Text>("Play", Config::GetValue<std::string>("font"), 1.0f);
    mPlayText->SetOrderLayer(1);
    mPlayText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });

    mPlayButton = Pong::AddUIElement<UIElement>();
    mPlayButton->UseMesh<Rectangle>(300.0f, 150.0f);
    mPlayButton->SetColliderBox(300.0f, 150.0f);
    mPlayButton->AddListener(UIEventType::Pressed, []() { LogInfo("Pressed"); });
    mPlayButton->AddListener(UIEventType::Release, []() { LogInfo("Release"); });
    mPlayButton->AddListener(UIEventType::Hover, []() { LogInfo("Hover"); });
    mPlayButton->AddListener(UIEventType::Unhover, []() { LogInfo("Unhover"); });
    LogInfo("mPlayButton: {}", mPlayButton->GetOrderLayer());
    //mPlayButton.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void TitleScreenController::PlayClicked()
{
    LogInfo("TitleScreenController::PlayClicked");
}

} // namespace pong
