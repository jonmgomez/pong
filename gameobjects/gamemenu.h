#pragma once

#include "behavior.h"
#include "mesh.h"
#include "text.h"

namespace pong
{

class GameMenu : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<GameMenu>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }

    void OnStart() override;
    void OnUpdate() override;

private:
    Mesh*     mSettingsBackground { nullptr };
    Text*     mSettingsText { nullptr };
    Text*     mTargetFPSText { nullptr };
    Slider*   mTargetFPSSlider { nullptr };
    CheckBox* mVSync { nullptr };
    Text*     mVSyncText { nullptr };
    Slider*   mVolumeSlider { nullptr };
    Text*     mVolumeText { nullptr };
    CheckBox* mSpatialAudio { nullptr };
    Text*     mSpatialAudioText { nullptr };
    bool mPaused { false };
};

} // namespace pong
