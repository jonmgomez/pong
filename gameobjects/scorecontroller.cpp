#include "scorecontroller.h"

#include "config.h"
#include "pong.h"

namespace pong
{

void ScoreController::OnStart()
{
    mPlayerScoreText = Pong::FindGameObjectByName("PlayerScoreText")->GetComponent<Text>();
    mOpponentScoreText = Pong::FindGameObjectByName("OpponentScoreText")->GetComponent<Text>();\
    ASSERT(mPlayerScoreText != nullptr && mOpponentScoreText != nullptr);
}

int ScoreController::GetPlayerScore() const
{
    return mPlayerScore;
}

void ScoreController::PlayerScored()
{
    mPlayerScore++;
    mPlayerScoreText->SetText(std::to_string(mPlayerScore));
}

int ScoreController::GetOpponentScore() const
{
    return mOpponentScore;
}

void ScoreController::OpponentScored()
{
    mOpponentScore++;
    mOpponentScoreText->SetText(std::to_string(mOpponentScore));
}

} // namespace pong
