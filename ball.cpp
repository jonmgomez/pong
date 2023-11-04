#include "ball.h"

#include "rectangle.h"

namespace pong
{

static constexpr float BALL_WIDTH = 25.0f;
static constexpr float BALL_SPEED = 4.5f;
static int id = 0;

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    SetInstanceName("Ball");
    mXSpeed = BALL_SPEED;
    mYSpeed = BALL_SPEED;
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + glm::vec3(mXSpeed, mYSpeed, 0.0f);
    SetPosition(newPosition);
}

void Ball::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "Player" || other.GetInstanceName() == "Opponent"
     || other.GetInstanceName() == "WallV")
    {
        mXSpeed = -mXSpeed;
    }
    else
    {
        mYSpeed = -mYSpeed;
    }
}

} // namespace pong
