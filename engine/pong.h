#pragma once

#include "audiomixer.h"
#include "collisionmanager.h"
#include "gameobject.h"
#include "text.h"
#include "timer.h"
#include "utils.h"

#include <chrono>
#include <memory>
#include <vector>
#include <functional>

namespace pong
{

class Pong
{
public:
    static Pong& GetInstance();

    static void Init();
    static void GameLoop();
    static void Cleanup();

    template<typename T>
    static T* FindGameObject()
    {
        for (auto& gameObject : GetInstance().mGameObjects)
        {
            auto castedGameObject = dynamic_cast<T*>(gameObject.get());
            if (castedGameObject != nullptr)
            {
                return castedGameObject;
            }
        }
        return nullptr;
    }

    static GameObject* FindGameObjectByName(const std::string& name);

    static Text* AddText(const std::string& text, const std::string& fontPath,
                         float scale, int pixelLineHeight = 128,
                         const glm::vec3& position = glm::vec3(0.0f));

    static void SetTimeout(int gameObjectId, std::chrono::duration<double> timeout, std::function<void()> callback);

    CollisionManager& GetCollisionManager();
    Timer& GetTimer();
    AudioMixer& GetAudioMixer();

private:
    Pong() = default;
    Pong(const Pong&) = delete;
    Pong& operator=(const Pong&) = delete;
    Pong(Pong&&) = delete;
    Pong& operator=(Pong&&) = delete;
    ~Pong() = default;

    std::vector<std::unique_ptr<GameObject>> mGameObjects {};
    std::vector<std::unique_ptr<Text>> mTexts {};

    CollisionManager mCollisionManager {};
    Timer mTimer {};
    AudioMixer mAudioMixer {};
    bool mFirstFrame { true };
};

} // namespace pong
