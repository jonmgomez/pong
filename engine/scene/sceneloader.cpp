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

SceneLoader::SceneLoader()
{
    // Engine components
    mComponentMappings["Transform"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Transform>();
    };

    mComponentMappings["Mesh"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Mesh>();
    };

    mComponentMappings["ColliderBox"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<ColliderBox>();
    };

    mComponentMappings["Slider"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Slider>();
    };

    mComponentMappings["CheckBox"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<CheckBox>();
    };

    mComponentMappings["Button"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Button>();
    };

    mComponentMappings["Text"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Text>();
    };

    // User defined components
    mComponentMappings["Player"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Player>();
    };

    mComponentMappings["Opponent"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Opponent>();
    };

    mComponentMappings["Ball"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<Ball>();
    };

    mComponentMappings["ScoreArea"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<ScoreArea>();
    };

    mComponentMappings["ScoreController"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<ScoreController>();
    };

    mComponentMappings["TitleScreenController"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<TitleScreenController>();
    };

    mComponentMappings["SettingsScreenController"] = [](GameObject* gameObject) {
        return gameObject->AddComponent<SettingsScreenController>();
    };
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

std::vector<std::unique_ptr<GameObject>> SceneLoader::LoadScene(const std::string& sceneName)
{
    ASSERT(mScenes.find(sceneName) != mScenes.end());
    const nlohmann::json& sceneJson = mScenes[sceneName];
    return LoadSceneFromJson(sceneJson);
}

std::vector<std::unique_ptr<GameObject>> SceneLoader::LoadSceneFromJson(const nlohmann::json& sceneJson)
{
    std::vector<std::unique_ptr<GameObject>> gameObjects {};

    const std::string sceneName = sceneJson["name"];
    LogDebug("Loading Scene: {}", sceneName);

    const auto startTime = std::chrono::high_resolution_clock::now();

    for (const auto& gameObjectJson : sceneJson["objects"])
    {
        const std::string gameObjectName = gameObjectJson["name"];
        LogDebug("New Object {}", gameObjectName);

        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
        gameObject->SetInstanceName(gameObjectName);

        for (const auto& componentJson : gameObjectJson["components"])
        {
            const std::string componentTypeName = componentJson["type"];

            // Add component to game object using the component mapping lambdas
            BaseComponent* newComponent = mComponentMappings[componentTypeName](gameObject.get());

            LogDebug("Object {} - Adding Component: {}", gameObjectName, componentJson["type"]);
            ComponentDeserializer componentDeserializer {};
            componentDeserializer.DeserializeComponent(newComponent, componentJson);
        }

        gameObjects.push_back(std::move(gameObject));
    }

    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    LogInfo("Loaded Scene: {}", sceneName);
    LogInfo("Total Objects: {}", gameObjects.size());
    LogInfo("Total Load Time: {}ms ({}s)", duration, duration / 1000.0f);

    return gameObjects;
}

} // namespace pong
