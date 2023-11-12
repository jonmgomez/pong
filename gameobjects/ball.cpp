#include "ball.h"

#include "opponent.h"
#include "player.h"
#include "pong.h"
#include "rectangle.h"

#include <spdlog/spdlog.h>

#include <random>

namespace pong
{

static constexpr float BALL_WIDTH = 20.0f;
static constexpr float BALL_SPEED_BOUNCE_INCREMENT = 0.5f;
static constexpr float Y_STARTING_POSITION_BOUNDS = 500.0f;

std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distStartDir(0, 1);
std::uniform_real_distribution<float> distYPos(-Y_STARTING_POSITION_BOUNDS, Y_STARTING_POSITION_BOUNDS);

void Ball::OnStart()
{
    mMesh = std::make_unique<Rectangle>(BALL_WIDTH, BALL_WIDTH);
    mColliderBox = std::make_unique<ColliderBox>(BALL_WIDTH, BALL_WIDTH);
    SetInstanceName("Ball");
    ResetBall();
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
        Pong::SetTimeout(GetId(), 3000, std::bind(&Ball::ResetBall, this));
    }
    else if (other.GetInstanceName() == "Player" || other.GetInstanceName() == "Opponent")
    {
        mSpeed += BALL_SPEED_BOUNCE_INCREMENT;

        const float yPosDiff = GetPosition().y - other.GetPosition().y;
        const float paddleHeight = other.GetColliderBox()->GetHeight();
        const float pointInHeight = paddleHeight / 2.0f - fabs(yPosDiff);

        float percent = fabs(pointInHeight / (paddleHeight / 2.0f));
        percent = std::max(0.35f, percent);
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

    const float yStartingPos = distYPos(generator);
    SetPosition(glm::vec3(0.0f, yStartingPos, 0.0f));

    const float xDir = distStartDir(generator) ? 1.0f : -1.0f;
    const float yDir = distStartDir(generator) ? 1.0f : -1.0f;
    mVelocity = glm::normalize(glm::vec3(xDir, yDir, 0.0f)) * mSpeed;
}

} // namespace pong
