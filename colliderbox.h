#pragma once

#include <glm/glm.hpp>

#include <array>

namespace pong
{

class ColliderBox
{
private:
    std::array<glm::vec3, 4>mBounds {};
    std::array<glm::vec3, 4>mPositionBounds {};

public:
    ColliderBox(float width, float height);

    void OnPositionUpdate(const glm::vec3& position);
    bool CheckForCollision(const ColliderBox& other) const;
    bool CheckPointInBounds(const glm::vec3& position) const;

    float GetHeight() const;
};

} // namespace pong
