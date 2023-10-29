#include "ball.h"

#include "rectangle.h"

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(25.0f, 25.0f);
    mSpeed = 3.5f;
}

void Ball::OnUpdate()
{
    mPosition.x += mSpeed;
    mPosition.y += mSpeed;
}
