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
    mPlayButton = globals::game::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        globals::game::LoadSceneNext("Game");
    });
    SetupButton(mPlayButton, mPlayButton->GetComponent<Text>());

    mSettingsButton = globals::game::FindGameObjectByName("SettingsButton")->GetComponent<Button>();
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        globals::game::LoadSceneNext("Settings");
    });
    SetupButton(mSettingsButton, mSettingsButton->GetComponent<Text>());

    mQuitButton = globals::game::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        globals::engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
