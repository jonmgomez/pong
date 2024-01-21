#include "ballmovement.h"

#include "audiomixer.h"
#include "config.h"
#include "logger.h"
#include "opponent.h"
#include "player.h"
#include "pong.h"
#include "random.h"
#include "rectangle.h"
#include "timer.h"

namespace pong
{

static constexpr float BALL_SPEED_BOUNCE_INCREMENT = 75.0f;
static constexpr float Y_STARTING_POSITION_BOUNDS = 500.0f;

static constexpr std::chrono::seconds BALL_RESET_WAIT_S { 3 };

void BallMovement::OnStart()
{
    mTransform = GetComponent<Transform>();
    ASSERT(mTransform != nullptr);
    ASSERT(mOpponent != nullptr);

    ResetBall();
}

void BallMovement::OnUpdate()
{
    const glm::vec3 newPosition = mTransform->mPosition + mVelocity * Timer::frameTime;
    mTransform->mPosition = newPosition;
}

void BallMovement::HitScoreArea()
{
    timer::SetTimeout(GetGameObjectId(), BALL_RESET_WAIT_S, [this] ()
    {
        this->ResetBall();
    });
}

void BallMovement::HitPaddle(GameObject& other)
{
    mSpeed += BALL_SPEED_BOUNCE_INCREMENT;

    const float yPosDiff = mTransform->mPosition.y - other.GetComponent<Transform>()->mPosition.y;
    const float paddleHeight = other.GetComponent<ColliderBox>()->GetHeight();
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

void BallMovement::HitWall()
{
    mSpeed += BALL_SPEED_BOUNCE_INCREMENT;
    mVelocity = glm::normalize(glm::vec3(mVelocity.x, -mVelocity.y, 0.0f)) * mSpeed;
}

void BallMovement::ResetBall()
{
    mSpeed = mStartSpeed;

    const float yStartingPos = Random::ValueInRange(-Y_STARTING_POSITION_BOUNDS, Y_STARTING_POSITION_BOUNDS);
    mTransform->mPosition = glm::vec3(0.0f, yStartingPos, 0.0f);

    const float xDir = Random::Bool() ? 1.0f : -1.0f;
    const float yDir = Random::Bool() ? 1.0f : -1.0f;
    mVelocity = glm::normalize(glm::vec3(xDir, yDir, 0.0f)) * mSpeed;

    mOpponent->OnBallVelocityChange(mVelocity);
}

glm::vec3 BallMovement::GetVelocity() const
{
    return mVelocity;
}

} // namespace pong
