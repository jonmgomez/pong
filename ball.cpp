#include "ball.h"

#include "opponent.h"
#include "player.h"
#include "rectangle.h"

namespace pong
{

static constexpr float BALL_WIDTH = 25.0f;
static constexpr float MAX_BALL_SPEED = 8.5f;
static int id = 0;

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    SetInstanceName("Ball");
    mXSpeed = MAX_BALL_SPEED / 2;
    mYSpeed = MAX_BALL_SPEED / 2;
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + glm::vec3(mXSpeed, mYSpeed, 0.0f);
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
        const float yPosDiff = GetPosition().y - other.GetPosition().y;
        const float paddleHeight = other.GetColliderBox()->GetHeight();
        const float pointInHeight = paddleHeight / 2 - abs(yPosDiff);
        float percent = abs(pointInHeight / (paddleHeight / 2));

        // clamp percent between 0.35 and 1.0
        percent = std::max(0.35f, percent);
        percent = std::min(1.0f, percent);

        mXSpeed = MAX_BALL_SPEED * percent;
        mYSpeed = MAX_BALL_SPEED * (1 - percent);

        if (other.GetInstanceName() == "Opponent")
        {
            mXSpeed = -mXSpeed;
        }

        if (yPosDiff < 0)
        {
            mYSpeed = -mYSpeed;
        }
    }
    else
    {
        mYSpeed = -mYSpeed;
    }
}

} // namespace pong
