#pragma once

#include "component.h"

#include <glm/glm.hpp>

#include <array>

namespace pong
{

class RectangleBounds
{
public:
    RectangleBounds() = default;
    RectangleBounds(float width, float height);

    RectangleBounds operator+(const glm::vec3& position);
    RectangleBounds operator-(const glm::vec3& position);

    bool CheckPointInBounds(const glm::vec3& position) const;

    std::array<glm::vec3, 4> mBounds {};
};

class ColliderBox : public Component<ColliderBox>
{
public:
    ColliderBox() = default;
    ColliderBox(float width, float height);

    RectangleBounds GetBounds() const;
    float GetWidth() const;
    void SetWidth(float width);
    float GetHeight() const;
    void SetHeight(float height);
    void Resize(float width, float height);

private:
    void RecalculateBounds();

    RectangleBounds mBounds {};
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
