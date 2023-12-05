#include "settingsscreencontroller.h"

#include "checkbox.h"
#include "config.h"
#include "difficulty.h"
#include "pong.h"

namespace pong
{

constexpr float VOLUME_MIN = 0.0f;
constexpr float VOLUME_MAX = 1.0f;
constexpr float VOLUME_STEP = 0.01f;

void SettingsScreenController::OnStart()
{
    mSettingsText = Pong::AddUIElement<Text>("Settings", Config::GetValue<std::string>("font"), 1.5f, 256);
    mSettingsText->SetPosition(glm::vec3(0.0f, 750.0f, 0.0f));

    mBackText = Pong::AddUIElement<Text>("Back", Config::GetValue<std::string>("font"), 1.0f, 75);
    mBackButton = Pong::AddUIElement<Button>(300.0f, 150.0f);
    mBackButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(Scene::TitleScreen);
    });
    SetupButton(mBackButton, mBackText, glm::vec3(-950.0f, -750.0f, 0.0f));

    const float startVolume = Pong::GetInstance().GetAudioMixer().GetVolume();
    mVolumeText = Pong::AddUIElement<Text>("Volume: " + std::to_string(static_cast<int>(startVolume * 100)), Config::GetValue<std::string>("font"), 1.0f, 75);
    mVolumeText->SetPosition(glm::vec3(-750.0f, -450.0f, 0.0f));

    mVolumeSlider = Pong::AddUIElement<Slider>(1000.0f, 100.0f, VOLUME_MIN, VOLUME_MAX, VOLUME_STEP, startVolume);
    mVolumeSlider->SetPosition(glm::vec3(200.0f, -450.0f, 0.0f));
    mVolumeSlider->AddValueChangeListener([this] (float newValue) {
        Pong::GetInstance().GetAudioMixer().SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(newValue * 100)));
    });

    mSpatialAudioText = Pong::AddUIElement<Text>("Spatial Audio", Config::GetValue<std::string>("font"), 1.0f, 75);
    mSpatialAudioText->SetPosition(glm::vec3(-750.0f, 150.0f, 0.0f));

    mSpatialAudio = Pong::AddUIElement<CheckBox>(100.0f, 100.0f, Pong::GetInstance().GetAudioMixer().GetSpatialAudioEnabled());
    mSpatialAudio->SetPosition(glm::vec3(200.0f, 150.0f, 0.0f));
    mSpatialAudio->AddValueChangeListener([] (bool value) {
        Pong::GetInstance().GetAudioMixer().SetSpatialAudioEnabled(value);
    });

    mDifficultyText = Pong::AddUIElement<Text>("Difficulty", Config::GetValue<std::string>("font"), 1.0f, 75);
    mDifficultyText->SetPosition(glm::vec3(-750.0f, 0.0f, 0.0f));

    const Difficulty::Level currentDifficulty = Difficulty::GetLevel();
    const std::array<std::string, 4> difficultyNames = { "Easy", "Medium", "Hard", "Impossible" };

    for (int i = 0; i < 4; i++)
    {
        const float x = i % 2 * 550.0f;
        const float y = (i < 2) * 150.0f;
        mDifficultyTexts[i] = Pong::AddUIElement<Text>(difficultyNames[i], Config::GetValue<std::string>("font"), 1.0f, 75);
        mDifficultyTexts[i]->SetPosition(glm::vec3(-75.0f + x, 0.0f - y, 0.0f));

        mDifficultyCheckBoxes[i] = Pong::AddUIElement<CheckBox>(100.0f, 100.0f, currentDifficulty == static_cast<Difficulty::Level>(i));
        mDifficultyCheckBoxes[i]->SetPosition(glm::vec3(200.0f + x, 0.0f - y, 0.0f));
        mDifficultyCheckBoxes[i]->AddValueChangeListener([&, i] (bool value) {
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
}

} // namespace pong
