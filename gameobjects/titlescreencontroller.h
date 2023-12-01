#pragma once

#include "button.h"
#include "gameobject.h"
#include "text.h"

namespace pong
{

class TitleScreenController : public GameObject
{
public:
    void OnStart() override;

private:
    void HoverOverButton(Button* button, Text* buttonText);
    void UnhoverOverButton(Button* button, Text* buttonText);

    Text*   mPongText { nullptr };
    Button* mPlayButton { nullptr };
    Text*   mPlayText   { nullptr };
    Button* mSettingsButton { nullptr };
    Text*   mSettingsText   { nullptr };
    Button* mQuitButton { nullptr };
    Text*   mQuitText   { nullptr };
};

} // namespace pong
