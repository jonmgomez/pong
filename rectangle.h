#pragma once

#include "indexbuffer.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <array>
#include <memory>

namespace pong
{

class Rectangle : public Mesh
{
private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };

public:
    Rectangle(float width, float height);
};

} // namespace pong
