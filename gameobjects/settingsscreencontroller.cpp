#include "settingsscreencontroller.h"

#include "applicationwindow.h"
#include "checkbox.h"
#include "config.h"
#include "difficulty.h"
#include "engine.h"
#include "pong.h"

namespace pong
{

static constexpr float SLIDER_WIDTH = 1000.0f;
static constexpr float SLIDER_HEIGHT = 100.0f;

static constexpr float VOLUME_MIN = 0.0f;
static constexpr float VOLUME_MAX = 1.0f;
static constexpr float VOLUME_STEP = 0.01f;

static constexpr float TARGET_FPS_MIN = 1.0f;
static constexpr float TARGET_FPS_MAX = 4000.0f;

static constexpr glm::vec3 SETTINGS_TEXT_POSITION = glm::vec3(0.0f, 750.0f, 0.0f);
static constexpr glm::vec3 BACK_TEXT_POSITION = glm::vec3(-950.0f, -750.0f, 0.0f);
static constexpr glm::vec3 BACK_BUTTON_POSITION = glm::vec3(-950.0f, -750.0f, 0.0f);
static constexpr glm::vec3 VSYNC_TEXT_POSITION = glm::vec3(-750.0f, 450.0f, 0.0f);
static constexpr glm::vec3 VSYNC_CHECKBOX_POSITION = glm::vec3(200.0f, 450.0f, 0.0f);
static constexpr glm::vec3 TARGET_FPS_TEXT_POSITION = glm::vec3(-750.0f, 300.0f, 0.0f);
static constexpr glm::vec3 TARGET_FPS_SLIDER_POSITION = glm::vec3(200.0f, 300.0f, 0.0f);
static constexpr glm::vec3 SPATIAL_AUDIO_TEXT_POSITION = glm::vec3(-750.0f, 150.0f, 0.0f);
static constexpr glm::vec3 SPATIAL_AUDIO_CHECKBOX_POSITION = glm::vec3(200.0f, 150.0f, 0.0f);
static constexpr glm::vec3 DIFFICULTY_TEXT_POSITION = glm::vec3(-750.0f, 0.0f, 0.0f);
static constexpr glm::vec3 VOLUME_TEXT_POSITION = glm::vec3(-750.0f, -450.0f, 0.0f);
static constexpr glm::vec3 VOLUME_SLIDER_POSITION = glm::vec3(200.0f, -450.0f, 0.0f);

static constexpr float DIFFICULTY_SPREAD_H = 550.0f;
static constexpr float DIFFICULTY_SPREAD_V = 150.0f;

void SettingsScreenController::OnStart()
{
    const std::string font = Config::GetValue<std::string>("font");

    mSettingsText = Pong::AddUIElement<Text>("Settings", font, 1.5f, 256);
    mSettingsText->SetPosition(SETTINGS_TEXT_POSITION);

    mBackText = Pong::AddUIElement<Text>("Back", font, 1.0f, 75);
    mBackButton = Pong::AddUIElement<Button>(300.0f, 150.0f);
    mBackButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Title);
    });
    SetupButton(mBackButton, mBackText, BACK_BUTTON_POSITION);

    mTargetFPSText = Pong::AddUIElement<Text>("Target FPS: " + std::to_string(static_cast<int>(Engine::GetTargetFPS())), font, 1.0f, 75);
    mTargetFPSText->SetPosition(TARGET_FPS_TEXT_POSITION);

    mTargetFPSSlider = Pong::AddUIElement<Slider>(SLIDER_WIDTH, SLIDER_HEIGHT, TARGET_FPS_MIN, TARGET_FPS_MAX, 1.0f, static_cast<float>(Engine::GetTargetFPS()));
    mTargetFPSSlider->SetPosition(TARGET_FPS_SLIDER_POSITION);
    mTargetFPSSlider->AddValueChangeListener([this] (float newValue) {
        Engine::SetTargetFPS(static_cast<int>(newValue));
        this->mTargetFPSText->SetText("Target FPS: " + std::to_string(static_cast<int>(newValue)));
    });

    mVSyncText = Pong::AddUIElement<Text>("VSync", font, 1.0f, 75);
    mVSyncText->SetPosition(VSYNC_TEXT_POSITION);

    mVSync = Pong::AddUIElement<CheckBox>(100.0f, 100.0f, Config::GetValue<bool>("vsync", ApplicationWindow::IsVSyncActive()));
    mVSync->SetPosition(VSYNC_CHECKBOX_POSITION);
    mVSync->AddValueChangeListener([] (bool value) {
        ApplicationWindow::SetVSync(value);
    });

    mSpatialAudioText = Pong::AddUIElement<Text>("Spatial Audio", font, 1.0f, 75);
    mSpatialAudioText->SetPosition(SPATIAL_AUDIO_TEXT_POSITION);

    mSpatialAudio = Pong::AddUIElement<CheckBox>(100.0f, 100.0f, Pong::GetInstance().GetAudioMixer().GetSpatialAudioEnabled());
    mSpatialAudio->SetPosition(SPATIAL_AUDIO_CHECKBOX_POSITION);
    mSpatialAudio->AddValueChangeListener([] (bool value) {
        Pong::GetInstance().GetAudioMixer().SetSpatialAudioEnabled(value);
    });

    mDifficultyText = Pong::AddUIElement<Text>("Difficulty", font, 1.0f, 75);
    mDifficultyText->SetPosition(DIFFICULTY_TEXT_POSITION);

    const Difficulty::Level currentDifficulty = Difficulty::GetLevel();
    const std::array<std::string, 4> difficultyNames = { "Easy", "Medium", "Hard", "Impossible" };

    for (int i = 0; i < 4; i++)
    {
        const float x = i % 2 * DIFFICULTY_SPREAD_H;
        const float y = (i < 2) * DIFFICULTY_SPREAD_V;
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

    const float startVolume = Pong::GetInstance().GetAudioMixer().GetVolume();
    mVolumeText = Pong::AddUIElement<Text>("Volume: " + std::to_string(static_cast<int>(startVolume * 100)), font, 1.0f, 75);
    mVolumeText->SetPosition(VOLUME_TEXT_POSITION);

    mVolumeSlider = Pong::AddUIElement<Slider>(SLIDER_WIDTH, SLIDER_HEIGHT, VOLUME_MIN, VOLUME_MAX, VOLUME_STEP, startVolume);
    mVolumeSlider->SetPosition(VOLUME_SLIDER_POSITION);
    mVolumeSlider->AddValueChangeListener([this] (float newValue) {
        Pong::GetInstance().GetAudioMixer().SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(roundf(newValue * 100.0f))));
    });
}

} // namespace pong
