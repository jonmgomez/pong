#include "scorecontroller.h"

#include "config.h"
#include "pong.h"

namespace pong
{

constexpr float SCORE_TEXT_SCALE = 1.0f;
constexpr int SCORE_TEXT_PIXEL_LINE_HEIGHT = 256;

ScoreTextBlueprint::ScoreTextBlueprint()
{
    SetInstanceName("ScoreText");
    AddComponent<Transform>();
    AddComponent<Text>("0", Config::GetValue<std::string>("font", ""), SCORE_TEXT_SCALE, SCORE_TEXT_PIXEL_LINE_HEIGHT);
}

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
