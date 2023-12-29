#include "colliderbox.h"

#include <glm/glm.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>

namespace pong
{

RectangleBounds::RectangleBounds(float width, float height) :
    mBounds {
        glm::vec3(-width / 2.0f, -height / 2.0f, 0.0f),
        glm::vec3( width / 2.0f,  height / 2.0f, 0.0f),
        glm::vec3(-width / 2.0f,  height / 2.0f, 0.0f),
        glm::vec3( width / 2.0f, -height / 2.0f, 0.0f)
    }
{
}

RectangleBounds RectangleBounds::operator+(const glm::vec3& position)
{
    RectangleBounds newBounds{};

    newBounds.mBounds[0] = mBounds[0] + position;
    newBounds.mBounds[1] = mBounds[1] + position;
    newBounds.mBounds[2] = mBounds[2] + position;
    newBounds.mBounds[3] = mBounds[3] + position;

    return newBounds;
}

RectangleBounds RectangleBounds::operator-(const glm::vec3& position)
{
    RectangleBounds newBounds{};

    newBounds.mBounds[0] = mBounds[0] - position;
    newBounds.mBounds[1] = mBounds[1] - position;
    newBounds.mBounds[2] = mBounds[2] - position;
    newBounds.mBounds[3] = mBounds[3] - position;

    return newBounds;
}

bool RectangleBounds::CheckPointInBounds(const glm::vec3& position) const
{
    return position.x >= mBounds[0].x && position.x <= mBounds[1].x
        && position.y >= mBounds[0].y && position.y <= mBounds[2].y;
}

ColliderBox::ColliderBox(float width, float height) :
    mWidth(width),
    mHeight(height)
{
    mBounds = { mWidth, mHeight };
}

RectangleBounds ColliderBox::GetBounds() const
{
    return mBounds;
}

float ColliderBox::GetWidth() const
{
    return mWidth;
}

void ColliderBox::SetWidth(float width)
{
    mWidth = width;
    mBounds = { mWidth, mHeight };
}

float ColliderBox::GetHeight() const
{
    return mHeight;
}

void ColliderBox::SetHeight(float height)
{
    mHeight = height;
    mBounds = { mWidth, mHeight };
}

void ColliderBox::Resize(float width, float height)
{
    mWidth = width;
    mHeight = height;
    mBounds = { mWidth, mHeight };
}

} // namespace pong
