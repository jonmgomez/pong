#pragma once

#include "gameobject.h"

namespace pong
{

class Wall : public GameObject
{
public:
    Wall(float width, float height);
};

} // namespace pong
