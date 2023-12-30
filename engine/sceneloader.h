#pragma once

#include <nlohmann/json.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pong
{

class GameObject;

class SceneLoader
{
public:
    SceneLoader();
    ~SceneLoader() = default;

    void PreLoadScenes();
    std::vector<std::unique_ptr<GameObject>> LoadScene(const std::string& sceneName);

private:
    std::vector<std::unique_ptr<GameObject>> LoadScene(const nlohmann::json& sceneJson);

    std::unordered_map<std::string, nlohmann::json> mScenes {};
    std::unordered_map<std::string, std::function<void(GameObject*)>> mComponentMappings {};
};

} // namespace pong
