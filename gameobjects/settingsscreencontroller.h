#pragma once

#include "button.h"
#include "gameobject.h"
#include "slider.h"
#include "text.h"

namespace pong
{

class SettingsScreenController : public GameObject
{
public:
    void OnStart() override;

private:
    Text* mSettingsText { nullptr };
    Button* mBackButton { nullptr };
    Text* mBackText { nullptr };
    Slider* mVolumeSlider { nullptr };
    Text* mVolumeText { nullptr };
};

} // namespace pong
