#include "config.h"

#include "renderutils.h"

#include <spdlog/spdlog.h>

#include <fstream>

namespace pong
{

Config& Config::GetInstance()
{
    static Config instance;
    return instance;
}

bool Config::LoadConfig(const std::string& filePath)
{
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open())
    {
        spdlog::error("Failed to open JSON config file: {}", filePath);
        return false;
    }

    nlohmann::json jsonData;

    try
    {
        jsonFile >> jsonData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        spdlog::error("JSON config parsing error: {}", e.what());
        return false;
    }

    GetInstance().mConfig = jsonData;
    return true;
}

std::optional<nlohmann::json> Config::GetJsonValue(const std::string& key)
{
    if (!GetInstance().mConfig.contains(key))
    {
        return {};
    }

    return GetInstance().mConfig[key];
}

} // namespace pong
