#include "wall.h"

#include "colliderbox.h"
#include "rectangle.h"

namespace pong
{

static int id = 0;

Wall::Wall(float width, float height)
{
    mMesh = std::make_unique<Rectangle>(width, height);
    mColliderBox = std::make_unique<ColliderBox>(width, height);
    mTag = "wall";
    mName = "Wall-" + std::to_string(id++);
}

} // namespace pong
