#pragma once

#include <nlohmann/json.hpp>

#include <optional>

namespace pong
{

class Config
{
private:
    nlohmann::json mConfig {};

public:
    static Config& GetInstance();
    static bool LoadConfig(const std::string& filePath);

    static std::optional<nlohmann::json> GetJsonValue(const std::string& key);

    template<typename T>
    static T GetValue(const std::string& key)
    {
        if (!GetInstance().mConfig.contains(key))
        {
            return T{};
        }

        try
        {
            return GetInstance().mConfig[key].get<T>();
        }
        catch(const std::exception&)
        {
            return T{};
        }
    }

    template<typename T>
    static T GetValue(const std::string& key, T defaultValue)
    {
        if (!GetInstance().mConfig.contains(key))
        {
            return defaultValue;
        }

        try
        {
            return GetInstance().mConfig[key].get<T>();
        }
        catch(const std::exception&)
        {
            return defaultValue;
        }
    }
};

} // namespace pong
