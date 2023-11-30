#pragma once

#include "gameobject.h"
#include "rectangle.h"
#include "text.h"
#include "uielement.h"

namespace pong
{

class TitleScreenController : public GameObject
{
public:
    void OnStart() override;

private:
    void HoverOverButton(UIElement* button, Text* buttonText);
    void UnhoverOverButton(UIElement* button, Text* buttonText);

    Text* mPongText { nullptr };
    UIElement* mPlayButton { nullptr };
    Text* mPlayText { nullptr };
    UIElement* mSettingsButton { nullptr };
    Text* mSettingsText { nullptr };
    UIElement* mQuitButton { nullptr };
    Text* mQuitText { nullptr };
};

} // namespace pong
