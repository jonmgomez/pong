#include "settingsscreencontroller.h"

#include "applicationwindow.h"
#include "checkbox.h"
#include "config.h"
#include "difficulty.h"
#include "engine.h"
#include "pong.h"

namespace pong
{

void SettingsScreenController::OnStart()
{
    mBackButton = globals::game::FindGameObjectByName("BackButton")->GetComponent<Button>();
    mBackButton->AddListener(ButtonEvent::Pressed, []() {
        globals::game::LoadSceneNext("Title");
    });
    SetupButton(mBackButton, mBackButton->GetComponent<Text>());

    const int targetFPS = globals::engine::GetTargetFPS();
    mTargetFPSText = globals::game::FindGameObjectByName("TargetFPSText")->GetComponent<Text>();
    mTargetFPSText->SetText("Target FPS: " + std::to_string(targetFPS));
    mTargetFPSSlider = globals::game::FindGameObjectByName("TargetFPSSlider")->GetComponent<Slider>();
    mTargetFPSSlider->SetValue(static_cast<float>(targetFPS));
    mTargetFPSSlider->AddValueChangeListener([this] (float newValue) {
        globals::engine::SetTargetFPS(static_cast<int>(newValue));
        this->mTargetFPSText->SetText("Target FPS: " + std::to_string(static_cast<int>(newValue)));
    });

    mVSync = globals::game::FindGameObjectByName("VSyncEnable")->GetComponent<CheckBox>();
    mVSync->SetValue(globals::application::IsVSyncActive());
    mVSync->AddValueChangeListener([] (bool value) {
        globals::application::SetVSync(value);
    });

    mSpatialAudio = globals::game::FindGameObjectByName("SpatialAudioEnable")->GetComponent<CheckBox>();
    mSpatialAudio->AddValueChangeListener([] (bool value) {
        globals::audio::SetSpatialAudioEnabled(value);
    });

    for (int i = 0; i < 4; i++)
    {
        mDifficultyCheckBoxes[i] = globals::game::FindGameObjectByName("DifficultyEnable" + std::to_string(i))->GetComponent<CheckBox>();
        mDifficultyCheckBoxes[i]->SetValue(Difficulty::GetLevel() == static_cast<Difficulty::Level>(i));
        mDifficultyCheckBoxes[i]->AddValueChangeListener([this, i] (bool value) {
            if (value)
            {
                Difficulty::SetLevel(static_cast<Difficulty::Level>(i));
                for (auto& checkBox : mDifficultyCheckBoxes)
                {
                    if (checkBox != mDifficultyCheckBoxes[i])
                    {
                        checkBox->SetValue(false);
                    }
                }
            }
        });
    }

    mVolumeText = globals::game::FindGameObjectByName("VolumeText")->GetComponent<Text>();
    const float volume = globals::audio::GetVolume();
    mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(volume * 100.0f)));
    mVolumeSlider = globals::game::FindGameObjectByName("VolumeSlider")->GetComponent<Slider>();
    mVolumeSlider->SetValue(volume);
    mVolumeSlider->AddValueChangeListener([this] (float newValue) {
        globals::audio::SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(roundf(newValue * 100.0f))));
    });
}

} // namespace pong
