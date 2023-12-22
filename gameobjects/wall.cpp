#include "wall.h"

#include "colliderbox.h"
#include "rectangle.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

WallBlueprint::WallBlueprint(float width, float height)
{
    SetInstanceName("Wall");
    AddComponent<Transform>();
    AddComponent<Rectangle>(width, height);
    AddComponent<ColliderBox>(width, height);
}

} // namespace pong
