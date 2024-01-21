#include "scorecontroller.h"

#include "config.h"
#include "pong.h"

namespace pong
{

void ScoreController::OnStart()
{
    ASSERT(mPlayerScoreText != nullptr && mOpponentScoreText != nullptr);
    mWinningScore = Config::GetValue("score_goal", 5);
}

int ScoreController::GetPlayerScore() const
{
    return mPlayerScore;
}

void ScoreController::PlayerScored()
{
    mPlayerScore++;
    mPlayerScoreText->SetText(std::to_string(mPlayerScore));
    CheckForWin();
}

int ScoreController::GetOpponentScore() const
{
    return mOpponentScore;
}

void ScoreController::OpponentScored()
{
    mOpponentScore++;
    mOpponentScoreText->SetText(std::to_string(mOpponentScore));
    CheckForWin();
}

void ScoreController::CheckForWin()
{
    if (mPlayerScore >= mWinningScore || mOpponentScore >= mWinningScore)
    {
        timer::SetTimeout(GetGameObjectId(), std::chrono::milliseconds(1000), []() {
            globals::game::LoadSceneNext("GameOver");
        });
    }
}

} // namespace pong
