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

void TitleScreenController::OnStart()
{
    mPlayButton = game::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        game::LoadSceneNext("Game");
    });
    SetupButton(mPlayButton, mPlayButton->GetComponent<Text>());

    mSettingsButton = game::FindGameObjectByName("SettingsButton")->GetComponent<Button>();
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        game::LoadSceneNext("Settings");
    });
    SetupButton(mSettingsButton, mSettingsButton->GetComponent<Text>());

    mQuitButton = game::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
