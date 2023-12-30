#pragma once

#include "graphic.h"

namespace pong
{

class Rectangle : public Graphic
{
public:
    Rectangle() = default;
    Rectangle(float width, float height);

    float GetWidth() const;
    float GetHeight() const;
    void Resize(float width, float height);

private:
    void RecomputeVertices();

    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

struct OffsetRectangle
{
    Rectangle mRectangle {};
    glm::vec3 mOffset { 0.0f, 0.0f, 0.0f };
};

} // namespace pong
