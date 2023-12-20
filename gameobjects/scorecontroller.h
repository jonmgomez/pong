#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "text.h"

namespace pong
{

class ScoreController : public Behavior, public BehaviorIDGenerator<ScoreController>
{
public:
    void OnStart() override;

    int GetPlayerScore() const;
    void PlayerScored();
    int GetOpponentScore() const;
    void OpponentScored();

private:
    int mPlayerScore { 0 };
    int mOpponentScore { 0 };

    Text* mPlayerScoreText { nullptr };
    Text* mOpponentScoreText { nullptr };
};

} // namespace pong
