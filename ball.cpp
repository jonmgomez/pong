#include "ball.h"

#include "opponent.h"
#include "player.h"
#include "rectangle.h"

namespace pong
{

static constexpr float BALL_WIDTH = 25.0f;
static constexpr float BALL_SPEED_BOUNCE_INCREMENT = 0.25f;

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    SetInstanceName("Ball");
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + mVelocity;
    SetPosition(newPosition);
}

void Ball::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "ScoreArea")
    {
        SetPosition(glm::vec3(0.0f));
    }
    else if (other.GetInstanceName() == "Player" || other.GetInstanceName() == "Opponent")
    {
        mSpeed += BALL_SPEED_BOUNCE_INCREMENT;

        const float yPosDiff = GetPosition().y - other.GetPosition().y;
        const float paddleHeight = other.GetColliderBox()->GetHeight();
        const float pointInHeight = paddleHeight / 2 - abs(yPosDiff);

        float percent = abs(pointInHeight / (paddleHeight / 2));
        percent = std::max(0.35f, percent);
        percent = std::min(1.0f, percent);

        float xDir = percent;
        float yDir = (1 - percent);

        if (other.GetInstanceName() == "Opponent")
        {
            xDir = -xDir;
        }

        if (yPosDiff < 0)
        {
            yDir = -yDir;
        }

        mVelocity = glm::normalize(glm::vec3(xDir, yDir, 0.0f)) * mSpeed;
    }
    else
    {
        mSpeed += BALL_SPEED_BOUNCE_INCREMENT;
        mVelocity = glm::normalize(glm::vec3(mVelocity.x, -mVelocity.y, 0.0f)) * mSpeed;
    }
}

} // namespace pong
