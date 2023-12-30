#pragma once

#include "behavior.h"
#include "button.h"
#include "gameobject.h"
#include "text.h"

namespace pong
{

class TitleScreenController : public Behavior
{
public:

    void ButtonHoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight);
    void ButtonUnhoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight);
    void SetupButton(Button* button, Text* text);
    int GetBehaviorId() const override { return GetIdFromBehavior<TitleScreenController>(); }
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
