#include "ball.h"

#include "logger.h"
#include "opponent.h"
#include "player.h"
#include "pong.h"
#include "random.h"
#include "rectangle.h"
#include "timer.h"

#include <spdlog/spdlog.h>

namespace pong
{

static constexpr float BALL_WIDTH = 20.0f;
static constexpr float BALL_SPEED_BOUNCE_INCREMENT = 75.0f;
static constexpr float Y_STARTING_POSITION_BOUNDS = 500.0f;

static constexpr std::chrono::seconds BALL_RESET_WAIT_S { 3 };

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    mOpponent = Pong::FindGameObject<Opponent>();
    SetInstanceName("Ball");

    ResetBall();
}

void Ball::OnUpdate()
{
    const glm::vec3 newPosition = GetPosition() + mVelocity * Timer::frameTime;
    SetPosition(newPosition);
}

void Ball::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "ScoreArea")
    {
        SetTimeout(BALL_RESET_WAIT_S, [this] ()
        {
            this->ResetBall();
        });
    }
    else if (other.GetInstanceName() == "Player" || other.GetInstanceName() == "Opponent")
    {
        mSpeed += BALL_SPEED_BOUNCE_INCREMENT;

        const float yPosDiff = GetPosition().y - other.GetPosition().y;
        const float paddleHeight = other.GetColliderBox()->GetHeight();
        const float pointInHeight = paddleHeight / 2.0f - fabs(yPosDiff);

        float percent = fabs(pointInHeight / (paddleHeight / 2.0f));
        percent = std::max(0.5f, percent);
        percent = std::min(1.0f, percent);

        float xDir = percent;
        float yDir = (1.0f - percent);

        if (other.GetInstanceName() == "Opponent")
        {
            xDir = -xDir;
        }

        if (yPosDiff < 0)
        {
            yDir = -yDir;
        }

        mVelocity = glm::normalize(glm::vec3(xDir, yDir, 0.0f)) * mSpeed;
        mOpponent->OnBallVelocityChange(mVelocity);
    }
    else
    {
        mSpeed += BALL_SPEED_BOUNCE_INCREMENT;
        mVelocity = glm::normalize(glm::vec3(mVelocity.x, -mVelocity.y, 0.0f)) * mSpeed;
    }
}

void Ball::ResetBall()
{
    mSpeed = BALL_START_SPEED;

    const float yStartingPos = Random::Range(-Y_STARTING_POSITION_BOUNDS, Y_STARTING_POSITION_BOUNDS);
    SetPosition(glm::vec3(0.0f, yStartingPos, 0.0f));

    const float xDir = Random::Bool() ? 1.0f : -1.0f;
    const float yDir = Random::Bool() ? 1.0f : -1.0f;
    mVelocity = glm::normalize(glm::vec3(xDir, yDir, 0.0f)) * mSpeed;

    mOpponent->OnBallVelocityChange(mVelocity);
}

glm::vec3 Ball::GetVelocity() const
{
    return mVelocity;
}

} // namespace pong
