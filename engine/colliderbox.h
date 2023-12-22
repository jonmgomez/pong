#pragma once

#include "component.h"

#include <glm/glm.hpp>

#include <array>

namespace pong
{

struct RectangleBounds
{
public:
    bool CheckPointInBounds(const glm::vec3& position) const;

    std::array<glm::vec3, 4> mBounds {};
};

class ColliderBox : public Component<ColliderBox>
{
public:
    ColliderBox(float width, float height);

    void OnPositionUpdate(const glm::vec3& position);
    bool CheckForCollision(const ColliderBox& other) const;
    bool CheckPointInBounds(const glm::vec3& position) const;

    float GetWidth() const;
    void SetWidth(float width);
    float GetHeight() const;
    void SetHeight(float height);
    void Resize(float width, float height);

private:
    void RecalculateBounds();

    RectangleBounds mRawBounds {};
    RectangleBounds mPositionBounds {};
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
