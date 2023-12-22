#pragma once

#include "behavior.h"
#include "gameobject.h"

namespace pong
{

class WallBlueprint : public GameObjectBlueprint
{
public:
    WallBlueprint(float width, float height);
};

} // namespace pong
