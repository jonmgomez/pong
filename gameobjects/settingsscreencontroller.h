#pragma once

#include "behavior.h"
#include "button.h"
#include "checkbox.h"
#include "gameobject.h"
#include "slider.h"
#include "text.h"
#include "uimenu.h"

namespace pong
{

class SettingsScreenController : public Behavior, public UIMenu
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<SettingsScreenController>(); }
    void OnStart() override;

private:
    Text*     mSettingsText { nullptr };
    Button*   mBackButton { nullptr };
    Text*     mBackText { nullptr };
    Text*     mTargetFPSText { nullptr };
    Slider*   mTargetFPSSlider { nullptr };
    CheckBox* mVSync { nullptr };
    Text*     mVSyncText { nullptr };
    Slider*   mVolumeSlider { nullptr };
    Text*     mVolumeText { nullptr };
    CheckBox* mSpatialAudio { nullptr };
    std::array<CheckBox*, 4> mDifficultyCheckBoxes {};
    std::array<Text*, 4>     mDifficultyTexts {};

    friend class ComponentDeserializer;
};

} // namespace pong
