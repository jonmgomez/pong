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
    mXSpeed = BALL_SPEED;
    mYSpeed = BALL_SPEED;
    mName = "Ball-" + std::to_string(id++);
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + glm::vec3(mXSpeed, mYSpeed, 0.0f);
    SetPosition(newPosition);
    std::cout << "Position: " << "(" << GetPosition().x << ", " << GetPosition().y << ")" << std::endl;
}

void Ball::OnCollision(GameObject& other)
{
    std::cout << "Ball collided with something" << std::endl;

    if (other.GetTag() == "paddle")
    {
        mXSpeed = -mXSpeed;
    }
    else
    {
        mYSpeed = -mYSpeed;
    }
}

} // namespace pong
