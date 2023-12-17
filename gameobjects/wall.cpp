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
    SetInstanceName("Wall");
}

void Wall::InitalizeComponents()
{
    AddComponent<Transform>();
    AddComponent<Rectangle>(mWidth, mHeight);
    AddComponent<ColliderBox>(mWidth, mHeight);
}

} // namespace pong
