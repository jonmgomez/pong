#pragma once

#include "button.h"
#include "checkbox.h"
#include "gameobject.h"
#include "slider.h"
#include "text.h"
#include "uimenu.h"

namespace pong
{

class SettingsScreenController : public GameObject, public UIMenu
{
public:
    void OnStart() override;

private:
    Text* mSettingsText { nullptr };
    Button* mBackButton { nullptr };
    Text* mBackText { nullptr };
    Slider* mVolumeSlider { nullptr };
    Text* mVolumeText { nullptr };
    CheckBox* mSpatialAudio { nullptr };
    Text* mSpatialAudioText { nullptr };
    Text* mDifficultyText { nullptr };
    std::array<CheckBox*, 4> mDifficultyCheckBoxes {};
    std::array<Text*, 4> mDifficultyTexts {};
};

} // namespace pong
