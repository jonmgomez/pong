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

    void CreateQuad(float width, float height);
    void SetDimensions(float width, float height);

    float GetWidth() const;
    float GetHeight() const;

private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
