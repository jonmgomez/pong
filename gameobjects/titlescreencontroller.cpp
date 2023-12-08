#include "titlescreencontroller.h"

#include "button.h"
#include "config.h"
#include "logger.h"
#include "slider.h"
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

    mPlayText = Pong::AddUIElement<Text>("Play", kFontPath, 1.0f);
    mPlayButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::Game);
    });
    SetupButton(mPlayButton, mPlayText, glm::vec3(0.0f));

    mSettingsText = Pong::AddUIElement<Text>("Settings", kFontPath, 1.0f, 75);
    mSettingsButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::Settings);
    });
    SetupButton(mSettingsButton, mSettingsText, SETTINGS_BUTTON_POSITION);

    mQuitText = Pong::AddUIElement<Text>("Quit", kFontPath, 1.0f, 75);
    mQuitButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::ExitGame();
    });
    SetupButton(mQuitButton, mQuitText, QUIT_BUTTON_POSITION);
}

} // namespace pong
