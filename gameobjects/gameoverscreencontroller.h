#pragma once

#include "behavior.h"
#include "button.h"
#include "text.h"
#include "uimenu.h"

namespace pong
{

class GameOverScreenController : public Behavior, public UIMenu
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<GameOverScreenController>(); }
    void OnStart() override;

private:
    bool mPlayerWon { false };
    Text* mResultText { nullptr };
    Button* mPlayAgainButton { nullptr };
    Button* mTitleScreenButton { nullptr };
    Button* mQuitButton { nullptr };

    friend class ComponentDeserializer;
};

} // namespace pong
