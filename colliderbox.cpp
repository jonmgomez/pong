#include "colliderbox.h"

#include <glm/glm.hpp>

#include <iostream>
#include <sstream>

namespace pong
{

ColliderBox::ColliderBox(float width, float height)
{
    mBounds = {
        glm::vec3(-width / 2.0f, -height / 2.0f, 0.0f),
        glm::vec3( width / 2.0f,  height / 2.0f, 0.0f),
        glm::vec3(-width / 2.0f,  height / 2.0f, 0.0f),
        glm::vec3( width / 2.0f, -height / 2.0f, 0.0f)
    };

    mPositionBounds = mBounds;
}

void ColliderBox::UpdatePositionBounds(const glm::vec3& position)
{
    mPositionBounds[0] = mBounds[0] + position;
    mPositionBounds[1] = mBounds[1] + position;
    mPositionBounds[2] = mBounds[2] + position;
    mPositionBounds[3] = mBounds[3] + position;
}

bool ColliderBox::CheckForCollision(const ColliderBox& other) const
{
    const std::array<glm::vec3, 4>otherBounds = other.mPositionBounds;

    // Check within own bounds
    for (const auto& position : otherBounds)
    {
        if (CheckPointInBounds(position))
        {
            return true;
        }
    }

    // Check within other collider's bounds. This is due to the
    // possibility of the other collider ecompassing this collider
    // If that occurs, the other colliders positions do not not appear
    // inside the bounds and would not register as collision
    for (const auto& position : mPositionBounds)
    {
        if (other.CheckPointInBounds(position))
        {
            return true;
        }
    }

    return false;
}

bool ColliderBox::CheckPointInBounds(const glm::vec3& position) const
{
    return position.x >= mPositionBounds[0].x && position.x <= mPositionBounds[1].x
        && position.y >= mPositionBounds[0].y && position.y <= mPositionBounds[2].y;
}

} // namespace pong
