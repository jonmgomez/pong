#include "scorecontroller.h"

#include "config.h"
#include "pong.h"

namespace pong
{

constexpr float PLAYER_SCORE_TEXT_X = -750.0f;
constexpr float OPPONENT_SCORE_TEXT_X = 750.0f;
constexpr float SCORE_TEXT_Y = 750.0f;
constexpr float SCORE_TEXT_SCALE = 1.0f;
constexpr int SCORE_TEXT_PIXEL_LINE_HEIGHT = 256;

void ScoreController::InitalizeComponents()
{
}

void ScoreController::OnStart()
{
    mPlayerScoreText = Pong::AddUIElement<Text>("0", Config::GetValue<std::string>("font"), SCORE_TEXT_SCALE, SCORE_TEXT_PIXEL_LINE_HEIGHT);
    mPlayerScoreText->SetPosition(glm::vec3(PLAYER_SCORE_TEXT_X, SCORE_TEXT_Y, 0.0f));

    mOpponentScoreText = Pong::AddUIElement<Text>("0", Config::GetValue<std::string>("font", ""), SCORE_TEXT_SCALE, SCORE_TEXT_PIXEL_LINE_HEIGHT);
    mOpponentScoreText->SetPosition(glm::vec3(OPPONENT_SCORE_TEXT_X, SCORE_TEXT_Y, 0.0f));
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
