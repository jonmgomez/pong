#include "gameoverscreencontroller.h"

#include "engine.h"
#include "gameobject.h"
#include "pong.h"
#include "scorecontroller.h"

namespace pong
{

void GameOverScreenController::OnStart()
{
    const ScoreController* score = Pong::FindComponentOfType<ScoreController>();
    ASSERT(score != nullptr);
    score->GetGameObject()->SetDestroyOnLoad(true);
    mPlayerWon = score->GetPlayerScore() > score->GetOpponentScore();

    mResultText = Pong::FindGameObjectByName("ResultText")->GetComponent<Text>();
    if (mPlayerWon)
    {
        mResultText->SetText("You won!");
    }
    else
    {
        mResultText->SetText("You lost!");
    }

    mPlayAgainButton = Pong::FindGameObjectByName("PlayButton")->GetComponent<Button>();
    mPlayAgainButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext("Game");
    });
    SetupButton(mPlayAgainButton, mPlayAgainButton->GetComponent<Text>());

    mTitleScreenButton = Pong::FindGameObjectByName("TitleButton")->GetComponent<Button>();
    mTitleScreenButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext("Title");
    });
    SetupButton(mTitleScreenButton, mTitleScreenButton->GetComponent<Text>());

    mQuitButton = Pong::FindGameObjectByName("QuitButton")->GetComponent<Button>();
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Engine::QuitApplication();
    });
    SetupButton(mQuitButton, mQuitButton->GetComponent<Text>());
}

} // namespace pong
