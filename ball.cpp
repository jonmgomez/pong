#include "ball.h"

#include "rectangle.h"

namespace pong
{

static constexpr float BALL_WIDTH = 25.0f;
static constexpr float BALL_SPEED = -1.5f;

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    mSpeed = BALL_SPEED;
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + glm::vec3(mSpeed, 0, 0.0f);
    SetPosition(newPosition);
    std::cout << "Position: " << "(" << GetPosition().x << ", " << GetPosition().y << ")" << std::endl;
}

void Ball::OnCollision(GameObject& /*other*/)
{
    std::cout << "Ball collided with something" << std::endl;
    mSpeed = -mSpeed;
}

} // namespace pong
