#pragma once

#include "gameobject.h"

#include <glm/glm.hpp>

namespace pong
{

class Player : public GameObject
{
private:
    static constexpr float PLAYER_SPEED = 2.5f;
    static constexpr float PLAYER_WIDTH = 25.0f;
    static constexpr float PLAYER_HEIGHT = 225.0f;

    float mSpeed { PLAYER_SPEED };
    float mHeight { PLAYER_HEIGHT };
    float mWidth { PLAYER_WIDTH };

public:
    void OnStart() override;
    void OnUpdate() override;

    float GetHeight() const;
    float GetWidth() const;
};

} // namespace pong
