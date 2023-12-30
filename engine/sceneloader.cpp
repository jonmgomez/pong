#include "sceneloader.h"

#include "ball.h"
#include "button.h"
#include "checkbox.h"
#include "colliderbox.h"
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

#include <fstream>

namespace pong
{

SceneLoader::SceneLoader()
{
    // Engine components
    mComponentMappings["Transform"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Transform>();
    };

    mComponentMappings["Mesh"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Mesh>();
    };

    mComponentMappings["ColliderBox"] = [](GameObject* gameObject) {
        gameObject->AddComponent<ColliderBox>();
    };

    mComponentMappings["Slider"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Slider>();
    };

    mComponentMappings["CheckBox"] = [](GameObject* gameObject) {
        gameObject->AddComponent<CheckBox>();
    };

    mComponentMappings["Button"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Button>();
    };

    mComponentMappings["Text"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Text>();
    };

    // User defined components
    mComponentMappings["Player"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Player>();
    };

    mComponentMappings["Opponent"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Opponent>();
    };

    mComponentMappings["Ball"] = [](GameObject* gameObject) {
        gameObject->AddComponent<Ball>();
    };

    mComponentMappings["ScoreArea"] = [](GameObject* gameObject) {
        gameObject->AddComponent<ScoreArea>();
    };

    mComponentMappings["ScoreController"] = [](GameObject* gameObject) {
        gameObject->AddComponent<ScoreController>();
    };

    mComponentMappings["TitleScreenController"] = [](GameObject* gameObject) {
        gameObject->AddComponent<TitleScreenController>();
    };

    mComponentMappings["SettingsScreenController"] = [](GameObject* gameObject) {
        gameObject->AddComponent<SettingsScreenController>();
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
        std::cout << "Parsing scene: " << sceneName << std::endl;

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
    return LoadScene(sceneJson);
}

std::vector<std::unique_ptr<GameObject>> SceneLoader::LoadScene(const nlohmann::json& sceneJson)
{
    std::vector<std::unique_ptr<GameObject>> gameObjects {};

    const std::string sceneName = sceneJson["name"];
    std::cout << "Parsing scene: " << sceneName << std::endl;

    for (const auto& gameObjectJson : sceneJson["objects"])
    {
        const std::string gameObjectName = gameObjectJson["name"];
        std::cout << "Parsing game object: " << gameObjectName << std::endl;

        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
        gameObject->SetInstanceName(gameObjectName);

        for (const auto& componentJson : gameObjectJson["components"])
        {
            std::string componentTypeName = componentJson["type"];
            std::cout << "Parsing component: " << componentTypeName << std::endl;

            // Add component to game object using the component mapping lambdas
            mComponentMappings[componentTypeName](gameObject.get());
        }

        gameObjects.push_back(std::move(gameObject));
    }

    return gameObjects;
}

} // namespace pong
