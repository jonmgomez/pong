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
public:
    Rectangle(float width, float height);

    float GetWidth() const;
    float GetHeight() const;
    void Resize(float width, float height);

private:
    void RecomputeVertices();

    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
