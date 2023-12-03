#include "settingsscreencontroller.h"

#include "config.h"
#include "pong.h"

namespace pong
{

constexpr float STARTING_VOLUME = 0.5f;

void SettingsScreenController::OnStart()
{
    mSettingsText = Pong::AddUIElement<Text>("Settings", Config::GetValue<std::string>("font"), 1.5f, 256);
    mSettingsText->SetPosition(glm::vec3(0.0f, 750.0f, 0.0f));

    mBackButton = Pong::AddUIElement<Button>(400.0f, 200.0f);
    mBackButton->SetPosition(glm::vec3(-900.0f, -700.0f, 0.0f));
    mBackButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::TitleScreen);
    });

    mBackText = Pong::AddUIElement<Text>("Back", Config::GetValue<std::string>("font"), 1.0f, 75);
    mBackText->SetOrderLayer(1);
    mBackText->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
    mBackText->SetPosition(glm::vec3(-900.0f, -700.0f, 0.0f));

    mVolumeText = Pong::AddUIElement<Text>("Volume: " + std::to_string(static_cast<int>(STARTING_VOLUME * 100)), Config::GetValue<std::string>("font"), 1.0f, 75);
    mVolumeText->SetOrderLayer(1);
    mVolumeText->SetPosition(glm::vec3(-450.0f, 0.0f, 0.0f));

    mVolumeSlider = Pong::AddUIElement<Slider>(1000.0f, 100.0f, 0.0f, 1.0f, 0.01f, STARTING_VOLUME);
    mVolumeSlider->SetPosition(glm::vec3(300.0f, 0.0f, 0.0f));
    mVolumeSlider->AddValueChangeListener([this](float newValue) {
        Pong::GetInstance().GetAudioMixer().SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(newValue * 100)));
    });
}

} // namespace pong
