#pragma once

#include "mesh.h"

namespace pong
{


class Circle : public Mesh
{
private:
    float mRadius { 0.0f };
    int mSides { 0 };
public:
    Circle(float radius, int sides);
};

} // namespace pong
