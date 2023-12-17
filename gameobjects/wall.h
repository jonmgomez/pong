#pragma once

#include "gameobject.h"

namespace pong
{

class Wall : public GameObject
{
public:
    Wall(float width, float height);

    void InitalizeComponents() override;

private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
