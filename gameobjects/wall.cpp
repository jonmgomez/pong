#include "wall.h"

#include "colliderbox.h"
#include "rectangle.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

WallBlueprint::WallBlueprint(float width, float height) :
    mWidth(width),
    mHeight(height)
{
    SetInstanceName("Wall");
    InitalizeComponents();
}

void WallBlueprint::InitalizeComponents()
{
    AddComponent<Transform>();
    AddComponent<Rectangle>(mWidth, mHeight);
    AddComponent<ColliderBox>(mWidth, mHeight);
}

} // namespace pong
