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
        engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
