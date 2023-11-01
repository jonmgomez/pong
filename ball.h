#pragma once

#include "gameobject.h"

namespace pong
{

class Ball : public GameObject
{
private:
    float mXSpeed { 0.0f };
    float mYSpeed { 0.0f };

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnCollision(GameObject& other) override;
};

} // namespace pong
