#pragma once

#include "behavior.h"
#include "button.h"
#include "gameobject.h"
#include "text.h"
#include "uimenu.h"

namespace pong
{

class TitleScreenController : public Behavior, public UIMenu
{
public:
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

    friend class ComponentDeserializer;
};

} // namespace pong
