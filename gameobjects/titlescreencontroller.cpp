#include "titlescreencontroller.h"

#include "button.h"
#include "logger.h"
#include "config.h"
#include "pong.h"

namespace pong
{

static constexpr float BUTTON_WIDTH = 400.0f;
static constexpr float BUTTON_HEIGHT = 200.0f;
static constexpr float HOVER_BUTTON_WIDTH = 400.0f * 1.35f;
static constexpr float HOVER_BUTTON_HEIGHT = 200.0f * 1.35f;
static constexpr GLRGBAColor IDLE_TEXT_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };
static constexpr glm::vec3 PONG_TEXT_POSITION(0.0f, 750.0f, 0.0f);
static constexpr glm::vec3 SETTINGS_BUTTON_POSITION(0.0f, -300.0f, 0.0f);
static constexpr glm::vec3 QUIT_BUTTON_POSITION(0.0f, -600.0f, 0.0f);

void TitleScreenController::OnStart()
{
    const std::string kFontPath = Config::GetValue<std::string>("font");
    mPongText = Pong::AddUIElement<Text>("Pong", kFontPath, 1.5f, 256);
    mPongText->SetPosition(PONG_TEXT_POSITION);



    mPlayButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);

    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::Game);
    });

    mPlayButton->AddListener(ButtonEvent::Hover, [this]() {
        this->HoverOverButton(mPlayButton, mPlayText);
    });

    mPlayButton->AddListener(ButtonEvent::Unhover, [this]() {
        this->UnhoverOverButton(mPlayButton, mPlayText);
    });

    mPlayText = Pong::AddUIElement<Text>("Play", kFontPath, 1.0f);
    mPlayText->SetOrderLayer(1);
    mPlayText->SetColor(IDLE_TEXT_COLOR);



    mSettingsButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mSettingsButton->SetPosition(SETTINGS_BUTTON_POSITION);

    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::Settings);
    });

    mSettingsButton->AddListener(ButtonEvent::Hover, [this]() {
        this->HoverOverButton(mSettingsButton, mSettingsText);
    });

    mSettingsButton->AddListener(ButtonEvent::Unhover, [this]() {
        this->UnhoverOverButton(mSettingsButton, mSettingsText);
    });

    mSettingsText = Pong::AddUIElement<Text>("Settings", kFontPath, 1.0f, 75);
    mSettingsText->SetOrderLayer(1);
    mSettingsText->SetColor(IDLE_TEXT_COLOR);
    mSettingsText->SetPosition(SETTINGS_BUTTON_POSITION);



    mQuitButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mQuitButton->SetPosition(QUIT_BUTTON_POSITION);

    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::ExitGame();
    });

    mQuitButton->AddListener(ButtonEvent::Hover, [this]() {
        this->HoverOverButton(mQuitButton, mQuitText);
    });

    mQuitButton->AddListener(ButtonEvent::Unhover, [this]() {
        this->UnhoverOverButton(mQuitButton, mQuitText);
    });

    mQuitText = Pong::AddUIElement<Text>("Quit", kFontPath, 1.0f, 75);
    mQuitText->SetOrderLayer(1);
    mQuitText->SetColor(IDLE_TEXT_COLOR);
    mQuitText->SetPosition(QUIT_BUTTON_POSITION);
}

void TitleScreenController::HoverOverButton(Button* button, Text* buttonText)
{
    button->Resize(HOVER_BUTTON_WIDTH, HOVER_BUTTON_HEIGHT);
    buttonText->SetColor(HOVER_TEXT_COLOR);
}

void TitleScreenController::UnhoverOverButton(Button* button, Text* buttonText)
{
    button->Resize(BUTTON_WIDTH, BUTTON_HEIGHT);
    buttonText->SetColor(IDLE_TEXT_COLOR);
}

} // namespace pong
