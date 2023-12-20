#pragma once

#include "behavior.h"
#include "gameobject.h"

namespace pong
{

class WallBlueprint : public GameObjectBlueprint
{
public:
    WallBlueprint(float width, float height);
    void InitalizeComponents() override;

private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
