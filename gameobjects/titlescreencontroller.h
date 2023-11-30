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
    void PlayClicked();

    Text* mPongText { nullptr };
    Text* mPlayText { nullptr };
    UIElement* mPlayButton { nullptr };
};

} // namespace pong
