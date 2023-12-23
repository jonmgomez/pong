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
    static constexpr float BUTTON_WIDTH = 400.0f;
    static constexpr float BUTTON_HEIGHT = 200.0f;
    static constexpr float HOVER_BUTTON_WIDTH = 400.0f * 1.35f;
    static constexpr float HOVER_BUTTON_HEIGHT = 200.0f * 1.35f;
    static constexpr GLRGBAColor IDLE_TEXT_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
    static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };
    static constexpr glm::vec3 PONG_TEXT_POSITION(0.0f, 750.0f, 0.0f);
    static constexpr glm::vec3 SETTINGS_BUTTON_POSITION(0.0f, -300.0f, 0.0f);
    static constexpr glm::vec3 QUIT_BUTTON_POSITION(0.0f, -600.0f, 0.0f);

    // GameObject* titleScreenController = NewObject();
    // titleScreenController->AddComponent<TitleScreenController>();

    const std::string kFontPath = Config::GetValue<std::string>("font");
    GameObject* pongText = NewObject();
    pongText->AddComponent<Text>("Pong", kFontPath, 1.5f, 256);
    pongText->AddComponent<Transform>(PONG_TEXT_POSITION);

    GameObject* playButton = NewObject();
    Button* buttonComponent = playButton->AddComponent<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    Text* textComponent = playButton->AddComponent<Text>("Play", kFontPath, 1.0f);

    buttonComponent->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Game);
    });
    SetupButton(buttonComponent, textComponent, glm::vec3(0.0f));

    mSettingsText = AddComponent<Text>("Settings", kFontPath, 1.0f, 75);
    mSettingsButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mSettingsButton->AddListener(ButtonEvent::Pressed, []() {
        Pong::LoadSceneNext(SceneType::Settings);
    });
    ->AddComponent<Transform>();
    SetupButton(mSettingsButton, mSettingsText, SETTINGS_BUTTON_POSITION);

    mQuitText = AddComponent<Text>("Quit", kFontPath, 1.0f, 75);
    mQuitButton = Pong::AddUIElement<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    mQuitButton->AddListener(ButtonEvent::Pressed, []() {
        Engine::QuitApplication();
    });
    ->AddComponent<Transform>();
    SetupButton(mQuitButton, mQuitText, QUIT_BUTTON_POSITION);
}
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
    SetNameAndPosition(topWall, "TopWall", glm::vec3(0.0f, horizontalWallY, 0.0f));

    GameObject* bottomWall = NewObjectFromBlueprint<WallBlueprint>(horizontalWallWidth, horizontalWallHeight);
    SetNameAndPosition(bottomWall, "BottomWall", glm::vec3(0.0f, -horizontalWallY, 0.0f));

    constexpr bool kPlayerScoreArea = true;
    GameObject* playerScoreArea = NewObjectFromBlueprint<ScoreAreaBlueprint>(verticalWallWidth, verticalWallHeight, kPlayerScoreArea);
    SetNameAndPosition(playerScoreArea, "PlayerScoreArea", glm::vec3(-verticalWallX, 0.0f, 0.0f));

    constexpr bool kOpponentScoreArea = false;
    GameObject* opponentScoreArea = NewObjectFromBlueprint<ScoreAreaBlueprint>(verticalWallWidth, verticalWallHeight, kOpponentScoreArea);
    SetNameAndPosition(opponentScoreArea, "OpponentScoreArea", glm::vec3(verticalWallX, 0.0f, 0.0f));

    GameObject* scoreController = NewObject();
    scoreController->AddComponent<ScoreController>();
}

} // namespace pong
