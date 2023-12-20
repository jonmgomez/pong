#include "pongscenes.h"

#include "ball.h"
#include "opponent.h"
#include "player.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "settingsscreencontroller.h"
#include "titlescreencontroller.h"
#include "wall.h"

namespace pong
{

void TitleScene::BuildScene()
{
    GameObject* titleScreenController = NewObject();
    titleScreenController->AddComponent<TitleScreenController>();
}

void SettingScene::BuildScene()
{
    GameObject* settingsScreenController = NewObject();
    settingsScreenController->AddComponent<SettingsScreenController>();
}

void GameScene::BuildScene()
{
    NewObjectFromBlueprint<PlayerBlueprint>();
    NewObjectFromBlueprint<OpponentBlueprint>();
    NewObjectFromBlueprint<BallBlueprint>();

    constexpr float horizontalWallWidth = 1280 * 2;
    constexpr float horizontalWallHeight = 25;
    constexpr float horizontalWallY = 960;
    constexpr float verticalWallWidth = 25;
    constexpr float verticalWallHeight = 960 * 2;
    constexpr float verticalWallX = 1280;

    GameObject* topWall = NewObjectFromBlueprint<WallBlueprint>(horizontalWallWidth, horizontalWallHeight);
    SetName(topWall, "TopWall");
    SetPosition(topWall, glm::vec3(0.0f, horizontalWallY, 0.0f));

    GameObject* bottomWall = NewObjectFromBlueprint<WallBlueprint>(horizontalWallWidth, horizontalWallHeight);
    SetName(bottomWall, "BottomWall");
    SetPosition(bottomWall, glm::vec3(0.0f, -horizontalWallY, 0.0f));

    constexpr bool kPlayerScoreArea = true;
    GameObject* playerScoreArea = NewObjectFromBlueprint<ScoreAreaBlueprint>(verticalWallWidth, verticalWallHeight, kPlayerScoreArea);
    SetName(playerScoreArea, "PlayerScoreArea");
    SetPosition(playerScoreArea, glm::vec3(-verticalWallX, 0.0f, 0.0f));

    constexpr bool kOpponentScoreArea = false;
    GameObject* opponentScoreArea = NewObjectFromBlueprint<ScoreAreaBlueprint>(verticalWallWidth, verticalWallHeight, kOpponentScoreArea);
    SetName(opponentScoreArea, "OpponentScoreArea");
    SetPosition(opponentScoreArea, glm::vec3(verticalWallX, 0.0f, 0.0f));

    GameObject* scoreController = NewObject();
    scoreController->AddComponent<ScoreController>();
}

} // namespace pong
