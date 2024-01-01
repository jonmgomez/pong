#pragma once

#include "component.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pong
{

class GameObject;

using GameObjectCollection = std::vector<std::unique_ptr<GameObject>>;

class SceneLoader
{
public:
    SceneLoader();
    ~SceneLoader() = default;

    void PreLoadScenes();
    GameObjectCollection LoadScene(const std::string& sceneName);

private:
    GameObjectCollection LoadSceneFromJson(const nlohmann::json& sceneJson);

    std::unordered_map<std::string, nlohmann::json> mScenes {};
    std::unordered_map<std::string, std::function<BaseComponent*(GameObject*)>> mComponentMappings {};
    nlohmann::json mCurrentComponentJson {};
};

} // namespace pong
