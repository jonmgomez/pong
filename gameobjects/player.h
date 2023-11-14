#pragma once

#include "gameobject.h"

#include <glm/glm.hpp>

namespace pong
{

class Player : public GameObject
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

private:
    static constexpr float PLAYER_WIDTH = 15.0f;
    static constexpr float PLAYER_HEIGHT = 125.0f;

    glm::vec3 mVelocity { 0.0f };
    float mHeight { PLAYER_HEIGHT };
    float mWidth { PLAYER_WIDTH };
};

} // namespace pong
