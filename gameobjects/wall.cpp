#include "wall.h"

#include "colliderbox.h"
#include "rectangle.h"
#include "transform.h"

namespace pong
{

Wall::Wall(float width, float height) :
    mWidth(width),
    mHeight(height)
{
    mMesh = std::make_unique<Rectangle>(width, height);
    mColliderBox = std::make_unique<ColliderBox>(width, height);
    SetInstanceName("Wall");
}

void Wall::InitalizeComponents()
{
    AddComponent<Transform>();
    AddComponent<Rectangle>(mWidth, mHeight);
    AddComponent<ColliderBox>(mWidth, mHeight);
}

} // namespace pong
