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
    mBackButton = Pong::FindGameObjectByName("BackButton")->GetComponent<Button>();
    mBackButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Title);
    });

    mTargetFPSText = Pong::FindGameObjectByName("TargetFPSText")->GetComponent<Text>();
    mTargetFPSSlider = Pong::FindGameObjectByName("TargetFPSSlider")->GetComponent<Slider>();
    mTargetFPSSlider->AddValueChangeListener([this] (float newValue) {
        Engine::SetTargetFPS(static_cast<int>(newValue));
        this->mTargetFPSText->SetText("Target FPS: " + std::to_string(static_cast<int>(newValue)));
    });

    mVSync = Pong::FindGameObjectByName("VSyncEnable")->GetComponent<CheckBox>();
    mVSync->AddValueChangeListener([] (bool value) {
        ApplicationWindow::SetVSync(value);
    });

    mSpatialAudio = Pong::FindGameObjectByName("SpatialAudioEnable")->GetComponent<CheckBox>();
    mSpatialAudio->AddValueChangeListener([] (bool value) {
        Pong::GetInstance().GetAudioMixer().SetSpatialAudioEnabled(value);
    });

    for (int i = 0; i < 4; i++)
    {
        mDifficultyCheckBoxes[i] = Pong::FindGameObjectByName("DifficultyEnable" + std::to_string(i))->GetComponent<CheckBox>();
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

    mVolumeText = Pong::FindGameObjectByName("VolumeText")->GetComponent<Text>();
    mVolumeSlider = Pong::FindGameObjectByName("VolumeSlider")->GetComponent<Slider>();
    mVolumeSlider->AddValueChangeListener([this] (float newValue) {
        Pong::GetInstance().GetAudioMixer().SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(roundf(newValue * 100.0f))));
    });
}

} // namespace pong
