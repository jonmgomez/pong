#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "text.h"

namespace pong
{

class ScoreController : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<ScoreController>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
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

    friend class ComponentDeserializer;
};

} // namespace pong
