#include "gamemenu.h"

#include "engine.h"
#include "logger.h"
#include "pong.h"
#include "timer.h"

namespace pong
{

void GameMenu::OnStart()
{
    mSettingsBackground = GetComponent<Mesh>();
    ASSERT(mSettingsBackground != nullptr);
    mSettingsBackground->SetEnabled(false);

    mSettingsText = globals::game::FindGameObjectByName("SettingsText")->GetComponent<Text>();
    ASSERT(mSettingsText != nullptr);
    mSettingsText->SetEnabled(false);

    const int targetFPS = globals::engine::GetTargetFPS();
    mTargetFPSText = globals::game::FindGameObjectByName("TargetFPSText")->GetComponent<Text>();
    ASSERT(mTargetFPSText != nullptr);
    mTargetFPSText->SetText("Target FPS: " + std::to_string(targetFPS));
    mTargetFPSText->SetEnabled(false);

    mTargetFPSSlider = globals::game::FindGameObjectByName("TargetFPSSlider")->GetComponent<Slider>();
    ASSERT(mTargetFPSSlider != nullptr);
    mTargetFPSSlider->SetValue(static_cast<float>(targetFPS));
    mTargetFPSSlider->SetEnabled(false);
    mTargetFPSSlider->AddValueChangeListener([this] (float newValue) {
        globals::engine::SetTargetFPS(static_cast<int>(newValue));
        this->mTargetFPSText->SetText("Target FPS: " + std::to_string(static_cast<int>(newValue)));
    });

    mVSync = globals::game::FindGameObjectByName("VSyncEnable")->GetComponent<CheckBox>();
    ASSERT(mVSync != nullptr);
    mVSync->SetValue(globals::application::IsVSyncActive());
    mVSync->SetEnabled(false);
    mVSync->AddValueChangeListener([] (bool value) {
        globals::application::SetVSync(value);
    });

    mVSyncText = globals::game::FindGameObjectByName("VSync")->GetComponent<Text>();
    ASSERT(mVSyncText != nullptr);
    mVSyncText->SetEnabled(false);

    mSpatialAudio = globals::game::FindGameObjectByName("SpatialAudioEnable")->GetComponent<CheckBox>();
    ASSERT(mSpatialAudio != nullptr);
    mSpatialAudio->SetValue(globals::audio::GetSpatialAudioEnabled());
    mSpatialAudio->SetEnabled(false);
    mSpatialAudio->AddValueChangeListener([] (bool value) {
        globals::audio::SetSpatialAudioEnabled(value);
    });

    mSpatialAudioText = globals::game::FindGameObjectByName("SpatialAudio")->GetComponent<Text>();
    ASSERT(mSpatialAudioText != nullptr);
    mSpatialAudioText->SetEnabled(false);

    const float volume = globals::audio::GetVolume();
    mVolumeSlider = globals::game::FindGameObjectByName("VolumeSlider")->GetComponent<Slider>();
    ASSERT(mVolumeSlider != nullptr);
    mVolumeSlider->SetValue(volume);
    mVolumeSlider->SetEnabled(false);
    mVolumeSlider->AddValueChangeListener([this] (float newValue) {
        globals::audio::SetVolume(newValue);
        this->mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(roundf(newValue * 100.0f))));
    });

    mVolumeText = globals::game::FindGameObjectByName("VolumeText")->GetComponent<Text>();
    ASSERT(mVolumeText != nullptr);
    mVolumeText->SetText("Volume: " + std::to_string(static_cast<int>(roundf(volume * 100.0f))));
    mVolumeText->SetEnabled(false);
}

void GameMenu::OnUpdate()
{
    if (globals::input::GetKeyState(GLFW_KEY_ESCAPE) == InputState::Pressed)
    {
        mPaused = !mPaused;

        timer::SetTimeScale(mPaused ? 0.0f : 1.0f);
        mSettingsBackground->SetEnabled(mPaused);
        mSettingsText->SetEnabled(mPaused);
        mTargetFPSText->SetEnabled(mPaused);
        mTargetFPSSlider->SetEnabled(mPaused);
        mVSync->SetEnabled(mPaused);
        mVSyncText->SetEnabled(mPaused);
        mSpatialAudio->SetEnabled(mPaused);
        mSpatialAudioText->SetEnabled(mPaused);
        mVolumeSlider->SetEnabled(mPaused);
        mVolumeText->SetEnabled(mPaused);
    }
}

} // namespace pong
