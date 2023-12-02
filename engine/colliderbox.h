#pragma once

#include <glm/glm.hpp>

#include <array>

namespace pong
{

class ColliderBox
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

    std::array<glm::vec3, 4> mBounds {};
    std::array<glm::vec3, 4> mPositionBounds {};
    float mWidth { 0.0f };
    float mHeight { 0.0f };
};

} // namespace pong
