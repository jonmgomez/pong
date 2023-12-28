#include "titlescreencontroller.h"

#include "button.h"
#include "config.h"
#include "engine.h"
#include "logger.h"
#include "slider.h"
#include "pong.h"

namespace pong
{

void TitleScreenController::OnStart()
{
    mPlayButton = Pong::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Game);
    });

    mSettingsButton = Pong::FindGameObjectByName("SettingsButton")->GetComponent<Button>();
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Settings);
    });

    mQuitButton = Pong::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Engine::QuitApplication();
    });
}

} // namespace pong
