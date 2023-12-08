#pragma once

#include "button.h"
#include "gameobject.h"
#include "text.h"
#include "uimenu.h"

namespace pong
{

class TitleScreenController : public GameObject, public UIMenu
{
public:
    void OnStart() override;

private:
    Text*   mPongText { nullptr };
    Button* mPlayButton { nullptr };
    Text*   mPlayText   { nullptr };
    Button* mSettingsButton { nullptr };
    Text*   mSettingsText   { nullptr };
    Button* mQuitButton { nullptr };
    Text*   mQuitText   { nullptr };
};

} // namespace pong
