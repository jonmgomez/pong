#include "gameoverscreencontroller.h"

#include "engine.h"
#include "gameobject.h"
#include "pong.h"
#include "scorecontroller.h"

namespace pong
{

void GameOverScreenController::OnStart()
{
    const ScoreController* score = globals::game::FindComponentOfType<ScoreController>();
    ASSERT(score != nullptr);
    score->GetGameObject()->SetDestroyOnLoad(true);
    mPlayerWon = score->GetPlayerScore() > score->GetOpponentScore();

    mResultText = globals::game::FindGameObjectByName("ResultText")->GetComponent<Text>();
    if (mPlayerWon)
    {
        mResultText->SetText("You won!");
    }
    else
    {
        mResultText->SetText("You lost!");
    }

    mPlayAgainButton = globals::game::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayAgainButton->AddListener(ButtonEvent::Pressed, []() {
        globals::game::LoadSceneNext("Game");
    });
    SetupButton(mPlayAgainButton, mPlayAgainButton->GetComponent<Text>());

    mTitleScreenButton = globals::game::FindGameObjectByName("TitleButton")->GetComponent<Button>();
    mTitleScreenButton->AddListener(ButtonEvent::Pressed, []() {
        globals::game::LoadSceneNext("Title");
    });
    SetupButton(mTitleScreenButton, mTitleScreenButton->GetComponent<Text>());

    mQuitButton = globals::game::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        globals::engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
