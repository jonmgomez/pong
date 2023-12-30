#include "titlescreencontroller.h"

#include "button.h"
#include "config.h"
#include "engine.h"
#include "logger.h"
#include "slider.h"
#include "pong.h"
#include "text.h"

namespace pong
{

static constexpr float BUTTON_WIDTH = 400.0f;
static constexpr float BUTTON_HEIGHT = 200.0f;
static constexpr float BUTTON_HOVER_SCALE = 1.35f;
static constexpr float HOVER_BUTTON_WIDTH = BUTTON_WIDTH * BUTTON_HOVER_SCALE;
static constexpr float HOVER_BUTTON_HEIGHT = BUTTON_HEIGHT * BUTTON_HOVER_SCALE;
static constexpr GLRGBAColor IDLE_TEXT_COLOR = GLRGBA_BLACK;
static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };

void TitleScreenController::ButtonHoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(HOVER_TEXT_COLOR);
}

void TitleScreenController::ButtonUnhoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(IDLE_TEXT_COLOR);
}

void TitleScreenController::SetupButton(Button* button, Text* text)
{
    text->SetColor(IDLE_TEXT_COLOR);
    text->SetOrderLayer(1);

    button->AddListener(ButtonEvent::Hover, [this, button, text]() {
        this->ButtonHoverAnimation(button, text, HOVER_BUTTON_WIDTH, HOVER_BUTTON_HEIGHT);
    });

    button->AddListener(ButtonEvent::Unhover, [this, button, text]() {
        this->ButtonUnhoverAnimation(button, text, BUTTON_WIDTH, BUTTON_HEIGHT);
    });
}

void TitleScreenController::OnStart()
{
    mPlayButton = Pong::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext("Game");
    });
    SetupButton(mPlayButton, mPlayButton->GetComponent<Text>());

    mSettingsButton = Pong::FindGameObjectByName("SettingsButton")->GetComponent<Button>();
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext("Settings");
    });
    SetupButton(mSettingsButton, mSettingsButton->GetComponent<Text>());

    mQuitButton = Pong::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
