#include "wall.h"

#include "rectangle.h"

namespace pong
{

static int id = 0;

Wall::Wall(float width, float height)
{
    mMesh = std::make_unique<Rectangle>(width, height);
    mName = "Wall";
}

} // namespace pong
