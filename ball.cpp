#include "ball.h"

#include "rectangle.h"

namespace pong
{

static constexpr float BALL_WIDTH = 25.0f;
static constexpr float BALL_SPEED = 3.5f;

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mSpeed = BALL_SPEED;
    mName = "Ball";
}

void Ball::OnUpdate()
{
    mPosition.x += mSpeed;
    mPosition.y += mSpeed;
}

} // namespace pong
