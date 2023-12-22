#include "colliderbox.h"

#include <glm/glm.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>

namespace pong
{

bool RectangleBounds::CheckPointInBounds(const glm::vec3& position) const
{
    return position.x >= mBounds[0].x && position.x <= mBounds[1].x
        && position.y >= mBounds[0].y && position.y <= mBounds[2].y;
}

ColliderBox::ColliderBox(float width, float height)
    : mWidth(width),
      mHeight(height)
{
    mRawBounds = {
        glm::vec3(-mWidth / 2.0f, -mHeight / 2.0f, 0.0f),
        glm::vec3( mWidth / 2.0f,  mHeight / 2.0f, 0.0f),
        glm::vec3(-mWidth / 2.0f,  mHeight / 2.0f, 0.0f),
        glm::vec3( mWidth / 2.0f, -mHeight / 2.0f, 0.0f)
    };

    mPositionBounds = mRawBounds;
}

void ColliderBox::OnPositionUpdate(const glm::vec3& position)
{
    mPositionBounds.mBounds[0] = mRawBounds.mBounds[0] + position;
    mPositionBounds.mBounds[1] = mRawBounds.mBounds[1] + position;
    mPositionBounds.mBounds[2] = mRawBounds.mBounds[2] + position;
    mPositionBounds.mBounds[3] = mRawBounds.mBounds[3] + position;
}

bool ColliderBox::CheckForCollision(const ColliderBox& other) const
{
    const std::array<glm::vec3, 4>& otherBounds = other.mPositionBounds.mBounds;
    // Check within own bounds
    if (std::any_of(std::begin(otherBounds), std::end(otherBounds),
        [&](const auto& position) { return mPositionBounds.CheckPointInBounds(position); }))
    {
        return true;
    }

    const std::array<glm::vec3, 4>& bounds = mPositionBounds.mBounds;
    // Check within other collider's bounds. This is due to the
    // possibility of the other collider ecompassing this collider
    // If that occurs, the other colliders positions do not not appear
    // inside the bounds and would not register as collision
    if (std::any_of(std::begin(bounds), std::end(bounds),
        [&other](const auto& position) { return other.mPositionBounds.CheckPointInBounds(position); }))
    {
        return true;
    }

    return false;
}

bool ColliderBox::CheckPointInBounds(const glm::vec3& position) const
{
    return mPositionBounds.CheckPointInBounds(position);
}

float ColliderBox::GetWidth() const
{
    return mWidth;
}

void ColliderBox::SetWidth(float width)
{
    mWidth = width;
    RecalculateBounds();
}

float ColliderBox::GetHeight() const
{
    return mHeight;
}

void ColliderBox::SetHeight(float height)
{
    mHeight = height;
    RecalculateBounds();
}

void ColliderBox::Resize(float width, float height)
{
    mWidth = width;
    mHeight = height;
    RecalculateBounds();
}

void ColliderBox::RecalculateBounds()
{
    // A little jank, but we need to figure out our current offset then reapply it
    const glm::vec3 position = mPositionBounds.mBounds[0] - mRawBounds.mBounds[0];

    mRawBounds = {
        glm::vec3(-mWidth / 2.0f, -mHeight / 2.0f, 0.0f),
        glm::vec3( mWidth / 2.0f,  mHeight / 2.0f, 0.0f),
        glm::vec3(-mWidth / 2.0f,  mHeight / 2.0f, 0.0f),
        glm::vec3( mWidth / 2.0f, -mHeight / 2.0f, 0.0f)
    };

    OnPositionUpdate(position);
}

} // namespace pong
