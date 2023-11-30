#include "titlescreencontroller.h"

#include "logger.h"
#include "config.h"
#include "pong.h"

namespace pong
{

static constexpr float BUTTON_WIDTH = 400.0f;
static constexpr float BUTTON_HEIGHT = 200.0f;

void TitleScreenController::OnStart()
{
    mPongText = Pong::AddText("Pong", Config::GetValue<std::string>("font"), 1.0f, 400);
    mPongText->SetPosition(glm::vec3(0.0f, 750.0f, 0.0f));


    mPlayButton = Pong::AddUIElement<UIElement>();
    mPlayButton->UseMesh<Rectangle>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mPlayButton->SetColliderBox(BUTTON_WIDTH, BUTTON_HEIGHT);

    mPlayButton->AddListener(UIEventType::Pressed, []() {
        Pong::LoadSceneNext(Scene::Game);
    });

    mPlayButton->AddListener(UIEventType::Hover, [this]() {
        this->HoverOverButton(mPlayButton, mPlayText);
    });

    mPlayButton->AddListener(UIEventType::Unhover, [this]() {
        this->UnhoverOverButton(mPlayButton, mPlayText);
    });

    mPlayText = Pong::AddUIElement<Text>("Play", Config::GetValue<std::string>("font"), 1.0f);
    mPlayText->SetOrderLayer(1);
    mPlayText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });



    mSettingsButton = Pong::AddUIElement<UIElement>();
    mSettingsButton->UseMesh<Rectangle>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mSettingsButton->SetColliderBox(BUTTON_WIDTH, BUTTON_HEIGHT);
    mSettingsButton->SetPosition(glm::vec3(0.0f, -300.0f, 0.0f));

    mSettingsButton->AddListener(UIEventType::Pressed, []() {
        Pong::LoadSceneNext(Scene::Settings);
    });

    mSettingsButton->AddListener(UIEventType::Hover, [this]() {
        this->HoverOverButton(mSettingsButton, mSettingsText);
    });

    mSettingsButton->AddListener(UIEventType::Unhover, [this]() {
        this->UnhoverOverButton(mSettingsButton, mSettingsText);
    });

    mSettingsText = Pong::AddUIElement<Text>("Settings", Config::GetValue<std::string>("font"), 1.0f, 75);
    mSettingsText->SetOrderLayer(1);
    mSettingsText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
    mSettingsText->SetPosition(glm::vec3(0.0f, -300.0f, 0.0f));


    mQuitButton = Pong::AddUIElement<UIElement>();
    mQuitButton->UseMesh<Rectangle>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mQuitButton->SetColliderBox(BUTTON_WIDTH, BUTTON_HEIGHT);
    mQuitButton->SetPosition(glm::vec3(0.0f, -600.0f, 0.0f));

    mQuitButton->AddListener(UIEventType::Pressed, []() {
        Pong::ExitGame();
    });

    mQuitButton->AddListener(UIEventType::Hover, [this]() {
        this->HoverOverButton(mQuitButton, mQuitText);
    });

    mQuitButton->AddListener(UIEventType::Unhover, [this]() {
        this->UnhoverOverButton(mQuitButton, mQuitText);
    });

    mQuitText = Pong::AddUIElement<Text>("Quit", Config::GetValue<std::string>("font"), 1.0f, 75);
    mQuitText->SetOrderLayer(1);
    mQuitText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
    mQuitText->SetPosition(glm::vec3(0.0f, -600.0f, 0.0f));
}

void TitleScreenController::HoverOverButton(UIElement* button, Text* buttonText)
{
    button->UseMesh<Rectangle>(BUTTON_WIDTH * 1.35f, 175.0f * 1.35f);
    buttonText->SetColor({ 0.4f, 0.4f, 0.4f, 1.0f });
}

void TitleScreenController::UnhoverOverButton(UIElement* button, Text* buttonText)
{
    button->UseMesh<Rectangle>(BUTTON_WIDTH, BUTTON_HEIGHT);
    buttonText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
}

} // namespace pong
