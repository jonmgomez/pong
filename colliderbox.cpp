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

std::string GetVec3String(const glm::vec3& vec)
{
    std::ostringstream oss;
    oss << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    std::string var = oss.str();
    return var;
}

void ColliderBox::UpdatePositionBounds(const glm::vec3& position)
{
    mPositionBounds[0] = mBounds[0] + position;
    mPositionBounds[1] = mBounds[1] + position;
    mPositionBounds[2] = mBounds[2] + position;
    mPositionBounds[3] = mBounds[3] + position;

    std::cout << "LL: " << GetVec3String(mPositionBounds[0]) << "\n";
    std::cout << "LR: " << GetVec3String(mPositionBounds[1]) << "\n";
    std::cout << "UR: " << GetVec3String(mPositionBounds[2]) << "\n";
    std::cout << "UL: " << GetVec3String(mPositionBounds[3]) << "\n";
}

bool ColliderBox::CheckForCollision(const ColliderBox& other) const
{
    const std::array<glm::vec3, 4>otherBounds = other.mPositionBounds;
    for (const auto& position : otherBounds)
    {
        if (CheckPointInBounds(position))
        {
            return true;
        }
    }
    return false;

} // namespace pong

bool ColliderBox::CheckPointInBounds(const glm::vec3& position) const
{
    return position.x >= mPositionBounds[0].x && position.x <= mPositionBounds[1].x
        && position.y >= mPositionBounds[0].y && position.y <= mPositionBounds[2].y;
}

} // namespace pong
