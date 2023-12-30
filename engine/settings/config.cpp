#include "config.h"

#include "logger.h"

#include <fstream>

namespace pong
{

static constexpr int PRINT_INDENTATION = 4;

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
        LogError("Failed to open JSON config file: {}", filePath);
        return false;
    }

    nlohmann::json jsonData;

    try
    {
        jsonFile >> jsonData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        LogError("JSON config parsing error: {}", e.what());
        return false;
    }

    GetInstance().mFilePath = filePath;
    GetInstance().mConfig = jsonData;
    return true;
}

void Config::SaveConfig()
{
    const std::string& filePath = GetInstance().mFilePath;
    std::ofstream jsonFile(filePath);
    if (!jsonFile.is_open())
    {
        LogError("Failed to open JSON config file: {}", filePath);
        return;
    }

    jsonFile << GetInstance().mConfig.dump(PRINT_INDENTATION);
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
