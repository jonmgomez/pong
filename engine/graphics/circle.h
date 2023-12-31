#pragma once

#include "mesh.h"

namespace pong
{


class Circle : public Graphic
{
public:
    Circle(float radius, int sides);

private:
    float mRadius { 0.0f };
    int mSides { 0 };
};

} // namespace pong
