#include "wall.h"

#include "colliderbox.h"
#include "rectangle.h"

namespace pong
{

Wall::Wall(float width, float height)
{
    mMesh = std::make_unique<Rectangle>(width, height);
    mColliderBox = std::make_unique<ColliderBox>(width, height);
}

} // namespace pong
