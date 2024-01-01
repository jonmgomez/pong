#include "sceneloader.h"

#include "ball.h"
#include "button.h"
#include "checkbox.h"
#include "colliderbox.h"
#include "componentdeserializer.h"
#include "config.h"
#include "gameobject.h"
#include "logger.h"
#include "mesh.h"
#include "player.h"
#include "opponent.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "settingsscreencontroller.h"
#include "slider.h"
#include "text.h"
#include "titlescreencontroller.h"
#include "transform.h"

#include <nlohmann/json.hpp>

#include <chrono>
#include <fstream>

namespace pong
{

template<typename T>
BaseComponent* AddComponentToObject(GameObject* gameObject)
{
    return gameObject->AddComponent<T>();
}

SceneLoader::SceneLoader()
{
    // Engine components
    mComponentMappings["Transform"] = &AddComponentToObject<Transform>;
    mComponentMappings["Mesh"] = &AddComponentToObject<Mesh>;
    mComponentMappings["ColliderBox"] = &AddComponentToObject<ColliderBox>;
    mComponentMappings["Slider"] = &AddComponentToObject<Slider>;
    mComponentMappings["CheckBox"] = &AddComponentToObject<CheckBox>;
    mComponentMappings["Button"] = &AddComponentToObject<Button>;
    mComponentMappings["Text"] = &AddComponentToObject<Text>;

    // User defined components
    mComponentMappings["Player"] = &AddComponentToObject<Player>;
    mComponentMappings["Opponent"] = &AddComponentToObject<Opponent>;
    mComponentMappings["Ball"] = &AddComponentToObject<Ball>;
    mComponentMappings["ScoreArea"] = &AddComponentToObject<ScoreArea>;
    mComponentMappings["ScoreController"] = &AddComponentToObject<ScoreController>;
    mComponentMappings["TitleScreenController"] = &AddComponentToObject<TitleScreenController>;
    mComponentMappings["SettingsScreenController"] = &AddComponentToObject<SettingsScreenController>;
}

void SceneLoader::PreLoadScenes()
{
    std::vector<std::string> sceneNames = Config::GetValue("scenes", std::vector<std::string> {});

    for (const auto& sceneName : sceneNames)
    {
        std::ifstream sceneFile { sceneName };

        if (!sceneFile.is_open())
        {
            LogError("Could not open scene file: {}", sceneName);
            ASSERT(false);
            continue;
        }

        nlohmann::json sceneJson;
        sceneFile >> sceneJson;

        if (sceneJson.is_null())
        {
            LogError("Scene file is empty: {}", sceneName);
            ASSERT(false);
            continue;
        }

        // Validating the scene file here saves some error checking later
        ASSERT(sceneJson.is_object());
        ASSERT(sceneJson.contains("name") && sceneJson["name"].is_string());
        const std::string sceneName = sceneJson["name"];

        ASSERT(sceneJson.contains("objects") && sceneJson["objects"].is_array());
        for (const auto& gameObjectJson : sceneJson["objects"])
        {
            ASSERT(gameObjectJson.is_object());
            ASSERT(gameObjectJson.contains("name") && gameObjectJson["name"].is_string());
            ASSERT(gameObjectJson.contains("components") && gameObjectJson["components"].is_array());
            for (const auto& componentJson : gameObjectJson["components"])
            {
                ASSERT(componentJson.is_object());
                ASSERT(componentJson.contains("type") && componentJson["type"].is_string());
                if (mComponentMappings.find(componentJson["type"]) == mComponentMappings.end())
                {
                    LogError("Unknown component type: {}", componentJson["type"]);
                    ASSERT(false);
                }
            }
        }

        ASSERT(mScenes.find(sceneName) == mScenes.end());
        mScenes[sceneName] = sceneJson;
    }
}

GameObjectCollection SceneLoader::LoadScene(const std::string& sceneName)
{
    if (mScenes.find(sceneName) == mScenes.end())
    {
        LogError("Scene {} does not exist!", sceneName);
        ASSERT(false);
        return {};
    }

    const nlohmann::json& sceneJson = mScenes[sceneName];
    return LoadSceneFromJson(sceneJson);
}

GameObjectCollection SceneLoader::LoadSceneFromJson(const nlohmann::json& sceneJson)
{
    GameObjectCollection gameObjects {};

    const std::string sceneName = sceneJson["name"];
    LogInfo("Loading Scene: {}", sceneName);

    int totalComponents = 0;
    const auto startTime = std::chrono::high_resolution_clock::now();

    for (const auto& gameObjectJson : sceneJson["objects"])
    {
        const std::string gameObjectName = gameObjectJson["name"];

        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
        gameObject->SetInstanceName(gameObjectName);

        for (const auto& componentJson : gameObjectJson["components"])
        {
            const std::string componentTypeName = componentJson["type"];

            // Add component to game object using the component mapping lambdas
            BaseComponent* newComponent = mComponentMappings[componentTypeName](gameObject.get());
            totalComponents++;

            ComponentDeserializer componentDeserializer {};
            componentDeserializer.DeserializeComponent(newComponent, componentJson);
        }

        gameObjects.push_back(std::move(gameObject));
    }

    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    LogInfo("Scene Loaded, Time Taken: {}ms ({}s). Total Objects: {} Total Components: {}",
        duration, duration / 1000.0f, gameObjects.size(), totalComponents);

    return gameObjects;
}

} // namespace pong
