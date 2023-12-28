#include "pongscenes.h"

#include "ball.h"
#include "button.h"
#include "config.h"
#include "difficulty.h"
#include "engine.h"
#include "opponent.h"
#include "player.h"
#include "pong.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "settingsscreencontroller.h"
#include "titlescreencontroller.h"
#include "wall.h"

namespace pong
{

static constexpr float BUTTON_WIDTH = 400.0f;
static constexpr float BUTTON_HEIGHT = 200.0f;
static constexpr float BUTTON_HOVER_SCALE = 1.35f;
static constexpr float HOVER_BUTTON_WIDTH = BUTTON_WIDTH * BUTTON_HOVER_SCALE;
static constexpr float HOVER_BUTTON_HEIGHT = BUTTON_HEIGHT * BUTTON_HOVER_SCALE;
static constexpr GLRGBAColor IDLE_TEXT_COLOR = GLRGBA_BLACK;
static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };

void ButtonHoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(HOVER_TEXT_COLOR);
}

void ButtonUnhoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(IDLE_TEXT_COLOR);
}

void SetupButton(Button* button, Text* text)
{
    text->SetColor(IDLE_TEXT_COLOR);
    text->SetOrderLayer(1);

    button->AddListener(ButtonEvent::Hover, [button, text]() {
        ButtonHoverAnimation(button, text, HOVER_BUTTON_WIDTH, HOVER_BUTTON_HEIGHT);
    });

    button->AddListener(ButtonEvent::Unhover, [button, text]() {
        ButtonUnhoverAnimation(button, text, BUTTON_WIDTH, BUTTON_HEIGHT);
    });
}

void TitleScene::BuildScene()
{
    static constexpr glm::vec3 PONG_TEXT_POSITION(0.0f, 750.0f, 0.0f);
    static constexpr glm::vec3 SETTINGS_BUTTON_POSITION(0.0f, -300.0f, 0.0f);
    static constexpr glm::vec3 QUIT_BUTTON_POSITION(0.0f, -600.0f, 0.0f);

    const std::string kFontPath = Config::GetValue<std::string>("font");
    GameObject* pongText = NewObject();
    pongText->AddComponent<Text>("Pong", kFontPath, 1.5f, 256);
    pongText->AddComponent<Transform>(PONG_TEXT_POSITION);

    GameObject* playButton = NewObject();
    playButton->SetInstanceName("PlayButton");
    playButton->AddComponent<Transform>();
    Button* buttonComponent = playButton->AddComponent<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    Text* textComponent = playButton->AddComponent<Text>("Play", kFontPath, 1.0f);
    SetupButton(buttonComponent, textComponent);

    GameObject* settingsButton = NewObject();
    settingsButton->SetInstanceName("SettingsButton");
    settingsButton->AddComponent<Transform>(SETTINGS_BUTTON_POSITION);
    buttonComponent = settingsButton->AddComponent<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    textComponent = settingsButton->AddComponent<Text>("Settings", kFontPath, 1.0f);
    SetupButton(buttonComponent, textComponent);

    GameObject* quitButton = NewObject();
    quitButton->SetInstanceName("QuitButton");
    quitButton->AddComponent<Transform>(QUIT_BUTTON_POSITION);
    buttonComponent = quitButton->AddComponent<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    textComponent = quitButton->AddComponent<Text>("Quit", kFontPath, 1.0f);
    SetupButton(buttonComponent, textComponent);
}

void SettingScene::BuildScene()
{
    static constexpr float SLIDER_WIDTH = 1000.0f;
    static constexpr float SLIDER_HEIGHT = 100.0f;

    static constexpr float CHECKBOX_WIDTH = 100.0f;
    static constexpr float CHECKBOX_HEIGHT = 100.0f;

    static constexpr float VOLUME_MIN = 0.0f;
    static constexpr float VOLUME_MAX = 1.0f;
    static constexpr float VOLUME_STEP = 0.01f;

    static constexpr float TARGET_FPS_MIN = 1.0f;
    static constexpr float TARGET_FPS_MAX = 4000.0f;

    static constexpr glm::vec3 SETTINGS_TEXT_POSITION = glm::vec3(0.0f, 750.0f, 0.0f);
    static constexpr glm::vec3 BACK_TEXT_POSITION = glm::vec3(-950.0f, -750.0f, 0.0f);
    static constexpr glm::vec3 BACK_BUTTON_POSITION = glm::vec3(-950.0f, -750.0f, 0.0f);
    static constexpr glm::vec3 VSYNC_TEXT_POSITION = glm::vec3(-750.0f, 450.0f, 0.0f);
    static constexpr glm::vec3 VSYNC_CHECKBOX_POSITION = glm::vec3(200.0f, 450.0f, 0.0f);
    static constexpr glm::vec3 TARGET_FPS_TEXT_POSITION = glm::vec3(-750.0f, 300.0f, 0.0f);
    static constexpr glm::vec3 TARGET_FPS_SLIDER_POSITION = glm::vec3(200.0f, 300.0f, 0.0f);
    static constexpr glm::vec3 SPATIAL_AUDIO_TEXT_POSITION = glm::vec3(-750.0f, 150.0f, 0.0f);
    static constexpr glm::vec3 SPATIAL_AUDIO_CHECKBOX_POSITION = glm::vec3(200.0f, 150.0f, 0.0f);
    static constexpr glm::vec3 DIFFICULTY_TEXT_POSITION = glm::vec3(-750.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 VOLUME_TEXT_POSITION = glm::vec3(-750.0f, -450.0f, 0.0f);
    static constexpr glm::vec3 VOLUME_SLIDER_POSITION = glm::vec3(200.0f, -450.0f, 0.0f);

    static constexpr float DIFFICULTY_SPREAD_H = 550.0f;
    static constexpr float DIFFICULTY_SPREAD_V = 150.0f;

    const std::string font = Config::GetValue<std::string>("font");

    GameObject* settingsText = NewObject();
    settingsText->AddComponent<Transform>(SETTINGS_TEXT_POSITION);
    settingsText->AddComponent<Text>("Settings", font, 1.5f, 256);

    GameObject* backButton = NewObject();
    backButton->SetInstanceName("BackButton");
    backButton->AddComponent<Transform>(BACK_BUTTON_POSITION);
    Button* buttonComponent = backButton->AddComponent<Button>(BUTTON_WIDTH, BUTTON_HEIGHT);
    Text* textComponent = backButton->AddComponent<Text>("Back", font, 1.0f, 75);
    SetupButton(buttonComponent, textComponent);

    GameObject* targetFPSText = NewObject();
    targetFPSText->SetInstanceName("TargetFPSText");
    targetFPSText->AddComponent<Transform>(TARGET_FPS_TEXT_POSITION);
    targetFPSText->AddComponent<Text>("Target FPS: " + std::to_string(static_cast<int>(Engine::GetTargetFPS())), font, 1.0f, 75);

    GameObject* targetFPSSlider = NewObject();
    targetFPSSlider->SetInstanceName("TargetFPSSlider");
    targetFPSSlider->AddComponent<Slider>(SLIDER_WIDTH, SLIDER_HEIGHT, TARGET_FPS_MIN, TARGET_FPS_MAX, 1.0f, static_cast<float>(Engine::GetTargetFPS()));
    targetFPSSlider->AddComponent<Transform>(TARGET_FPS_SLIDER_POSITION);

    GameObject* vSyncText = NewObject();
    vSyncText->AddComponent<Text>("VSync", font, 1.0f, 75);
    vSyncText->AddComponent<Transform>(VSYNC_TEXT_POSITION);

    GameObject* vSyncBox = NewObject();
    vSyncBox->SetInstanceName("VSyncEnable");
    vSyncBox->AddComponent<CheckBox>(CHECKBOX_WIDTH, CHECKBOX_HEIGHT, Config::GetValue<bool>("vsync", ApplicationWindow::IsVSyncActive()));
    vSyncBox->AddComponent<Transform>(VSYNC_CHECKBOX_POSITION);

    GameObject* spatialAudioText = NewObject();
    spatialAudioText->AddComponent<Text>("Spatial Audio", font, 1.0f, 75);
    spatialAudioText->AddComponent<Transform>(SPATIAL_AUDIO_TEXT_POSITION);

    GameObject* spatialAudio = NewObject();
    spatialAudio->SetInstanceName("SpatialAudioEnable");
    spatialAudio->AddComponent<CheckBox>(CHECKBOX_WIDTH, CHECKBOX_HEIGHT, Pong::GetInstance().GetAudioMixer().GetSpatialAudioEnabled());
    spatialAudio->AddComponent<Transform>(SPATIAL_AUDIO_CHECKBOX_POSITION);

    GameObject* difficultyText = NewObject();
    difficultyText->AddComponent<Text>("Difficulty", font, 1.0f, 75);
    difficultyText->AddComponent<Transform>(DIFFICULTY_TEXT_POSITION);

    const Difficulty::Level currentDifficulty = Difficulty::GetLevel();
    const std::array<std::string, 4> difficultyNames = { "Easy", "Medium", "Hard", "Impossible" };

    std::array<GameObject*, 4> mDifficultyTexts;
    std::array<GameObject*, 4> mDifficultyCheckBoxes;

    for (int i = 0; i < 4; i++)
    {
        const float x = i % 2 * DIFFICULTY_SPREAD_H;
        const float y = (i < 2) * DIFFICULTY_SPREAD_V;
        mDifficultyTexts[i] = NewObject();
        mDifficultyTexts[i]->AddComponent<Transform>(glm::vec3(-75.0f + x, 0.0f - y, 0.0f));
        mDifficultyTexts[i]->AddComponent<Text>(difficultyNames[i], font, 1.0f, 75);

        mDifficultyCheckBoxes[i] = NewObject();
        mDifficultyCheckBoxes[i]->SetInstanceName("DifficultyEnable" + std::to_string(i));
        mDifficultyCheckBoxes[i]->AddComponent<Transform>(glm::vec3(200.0f + x, 0.0f - y, 0.0f));
        mDifficultyCheckBoxes[i]->AddComponent<CheckBox>(100.0f, 100.0f, currentDifficulty == static_cast<Difficulty::Level>(i));
    }

    const float startVolume = Pong::GetInstance().GetAudioMixer().GetVolume();
    GameObject* volumeText = NewObject();
    volumeText->SetInstanceName("VolumeText");
    volumeText->AddComponent<Text>("Volume: " + std::to_string(static_cast<int>(startVolume * 100)), font, 1.0f, 75);
    volumeText->AddComponent<Transform>(VOLUME_TEXT_POSITION);

    GameObject* volumeSlider = NewObject();
    volumeSlider->SetInstanceName("VolumeSlider");
    volumeSlider->AddComponent<Slider>(SLIDER_WIDTH, SLIDER_HEIGHT, VOLUME_MIN, VOLUME_MAX, VOLUME_STEP, startVolume);
    volumeSlider->AddComponent<Transform>(VOLUME_SLIDER_POSITION);

    GameObject* settingsScreenController = NewObject();
    settingsScreenController->AddComponent<SettingsScreenController>();
}

void GameScene::BuildScene()
{
    static constexpr float PLAYER_SCORE_TEXT_X = -750.0f;
    static constexpr float OPPONENT_SCORE_TEXT_X = 750.0f;
    static constexpr float SCORE_TEXT_Y = 750.0f;

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

    GameObject* playerScoreText = NewObjectFromBlueprint<ScoreTextBlueprint>();
    SetNameAndPosition(playerScoreText, "PlayerScoreText", glm::vec3(PLAYER_SCORE_TEXT_X, SCORE_TEXT_Y, 0.0f));

    GameObject* opponentScoreText = NewObjectFromBlueprint<ScoreTextBlueprint>();
    SetNameAndPosition(opponentScoreText, "OpponentScoreText", glm::vec3(OPPONENT_SCORE_TEXT_X, SCORE_TEXT_Y, 0.0f));

    GameObject* scoreController = NewObject();
    scoreController->AddComponent<ScoreController>();
}

} // namespace pong
