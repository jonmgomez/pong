#include "titlescreencontroller.h"

#include "button.h"
#include "logger.h"
#include "config.h"
#include "pong.h"

namespace pong
{

static constexpr float BUTTON_WIDTH = 400.0f;
static constexpr float BUTTON_HEIGHT = 200.0f;
static constexpr GLRGBAColor IDLE_TEXT_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };

void TitleScreenController::OnStart()
{
    const std::string kFontPath = Config::GetValue<std::string>("font");
    mPongText = Pong::AddText("Pong", kFontPath, 1.5f, 256);
    mPongText->SetPosition(glm::vec3(0.0f, 750.0f, 0.0f));



    mPlayButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);

    mPlayButton->AddListener(UIEventType::Pressed, []() {
        Pong::LoadSceneNext(Scene::Game);
    });

    mPlayButton->AddListener(UIEventType::Hover, [this]() {
        this->HoverOverButton(mPlayButton, mPlayText);
    });

    mPlayButton->AddListener(UIEventType::Unhover, [this]() {
        this->UnhoverOverButton(mPlayButton, mPlayText);
    });

    mPlayText = Pong::AddUIElement<Text>("Play", kFontPath, 1.0f);
    mPlayText->SetOrderLayer(1);
    mPlayText->SetColor(IDLE_TEXT_COLOR);



    mSettingsButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
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

    mSettingsText = Pong::AddUIElement<Text>("Settings", kFontPath, 1.0f, 75);
    mSettingsText->SetOrderLayer(1);
    mSettingsText->SetColor(IDLE_TEXT_COLOR);
    mSettingsText->SetPosition(glm::vec3(0.0f, -300.0f, 0.0f));



    mQuitButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
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

    mQuitText = Pong::AddUIElement<Text>("Quit", kFontPath, 1.0f, 75);
    mQuitText->SetOrderLayer(1);
    mQuitText->SetColor(IDLE_TEXT_COLOR);
    mQuitText->SetPosition(glm::vec3(0.0f, -600.0f, 0.0f));
}

void TitleScreenController::HoverOverButton(Button* button, Text* buttonText)
{
    button->Resize(BUTTON_WIDTH * 1.35f, BUTTON_HEIGHT * 1.35f);
    buttonText->SetColor(HOVER_TEXT_COLOR);
}

void TitleScreenController::UnhoverOverButton(Button* button, Text* buttonText)
{
    button->Resize(BUTTON_WIDTH, BUTTON_HEIGHT);
    buttonText->SetColor(IDLE_TEXT_COLOR);
}

} // namespace pong
