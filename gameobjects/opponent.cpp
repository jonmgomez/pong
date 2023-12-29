#include "opponent.h"

#include "difficulty.h"
#include "logger.h"
#include "random.h"
#include "pong.h"
#include "rectangle.h"
#include "timer.h"

#include <glm/glm.hpp>

#include <iostream>

namespace pong
{

static constexpr float OPPONENT_WIDTH = 15.0f;
static constexpr float OPPONENT_HEIGHT = 125.0f;
static constexpr glm::vec3 OPPONENT_POSITION(1125.0f, 0.0f, 0.0f);

// Difficulty settings
static int decisionTimeLowerBoundMs = 50;
static int decisionTimeUpperBoundMs = 250;
static float baseMissChance = 0.1f;

OpponentBlueprint::OpponentBlueprint()
{
    SetInstanceName("Opponent");
    AddComponent<Transform>(OPPONENT_POSITION);
    AddComponent<Mesh>(std::make_unique<Rectangle>(OPPONENT_WIDTH, OPPONENT_HEIGHT));
    AddComponent<ColliderBox>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    AddComponent<Opponent>();
}

void Opponent::OnStart()
{
    SetDifficultySettings();

    mTransform = GetComponent<Transform>();
    mCollider = GetComponent<ColliderBox>();
    mTargetPosition = OPPONENT_POSITION;
    mBall = Pong::FindComponentOfType<Ball>();

    GameObject* topWall = Pong::FindGameObjectByName("TopWall");
    GameObject* bottomWall = Pong::FindGameObjectByName("BottomWall");

    ASSERT(bottomWall != nullptr && topWall != nullptr);

    mTopWallBound = topWall->GetComponent<Transform>()->mPosition.y;
    mBottomWallBound = bottomWall->GetComponent<Transform>()->mPosition.y;

    ASSERT(mTransform != nullptr && mCollider != nullptr);
    ASSERT(mBall != nullptr)
}

void Opponent::OnUpdate()
{
    if (mChasingBall)
    {
        const glm::vec3 currentPosition = mTransform->mPosition;
        const float distance = glm::distance(currentPosition, mTargetPosition);
        if (distance > (mSpeed * Timer::frameTime))
        {
            mVelocity = glm::normalize(mTargetPosition - currentPosition) * mSpeed * Timer::frameTime;
            mTransform->mPosition += mVelocity;
        }
        else
        {
            mTransform->mPosition = mTargetPosition;
        }
    }
}

void Opponent::SetDifficultySettings()
{
    switch (Difficulty::GetLevel())
    {
        case Difficulty::Level::Easy:
            decisionTimeLowerBoundMs = 200;
            decisionTimeUpperBoundMs = 500;
            baseMissChance = 0.f;
            break;

        case Difficulty::Level::Normal:
            decisionTimeLowerBoundMs = 100;
            decisionTimeUpperBoundMs = 350;
            baseMissChance = 0.2f;
            break;

        case Difficulty::Level::Hard:
            decisionTimeLowerBoundMs = 50;
            decisionTimeUpperBoundMs = 100;
            baseMissChance = 0.05f;
            break;

        case Difficulty::Level::Insane:
            decisionTimeLowerBoundMs = 0;
            decisionTimeUpperBoundMs = 0;
            baseMissChance = 0.0f;
            break;

        default:
            ASSERT(false);
            break;
    }
}

void Opponent::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName().find("Wall") != std::string::npos)
    {
        // Undo movement to stop from going through wall
        mTransform->mPosition -= mVelocity * Timer::frameTime;
    }
}

void Opponent::OnCollisionStay(GameObject& other)
{
    OnCollisionStart(other);
}

void Opponent::PredictBallPostion()
{
    const glm::vec3 currentPosition = mTransform->mPosition;
    const glm::vec3 ballPosition = mBall->GetComponent<Transform>()->mPosition;
    glm::vec3 ballVelocity = mBall->GetVelocity() * Timer::frameTime;
    glm::vec3 finalBallPosition = ballPosition;

    while (finalBallPosition.x < currentPosition.x)
    {
        finalBallPosition += ballVelocity;
        if (finalBallPosition.y >= mTopWallBound || finalBallPosition.y <= mBottomWallBound)
        {
            ballVelocity.y = -ballVelocity.y;
        }
    }

    const bool miss = Random::RollPercentChance(baseMissChance);
    if (miss)
    {
        const float minMissDistance = 150.0f;
        const float maxMissDistance = 225.0f;

        bool overShootUp = Random::Bool();
        if (overShootUp && mTopWallBound - currentPosition.y < maxMissDistance)
        {
            overShootUp = false;
        }
        if (!overShootUp && currentPosition.y - mBottomWallBound < maxMissDistance)
        {
            overShootUp = true;
        }

        const float error = Random::ValueInRange(minMissDistance, maxMissDistance);
        if (overShootUp)
        {
            finalBallPosition.y += error;
        }
        else
        {
            finalBallPosition.y -= error;
        }
    }
    else
    {
        // Add some error to the final ball position
        // So the paddle does not always hit the ball perfectly
        const float errorBound = mCollider->GetHeight() / 4.0f;
        finalBallPosition.y += Random::ValueInRange(-errorBound, errorBound);
    }

    mTargetPosition = glm::vec3(currentPosition.x, finalBallPosition.y, 0.0f);
}

void Opponent::OnBallVelocityChange(const glm::vec3& velocity)
{
    mChasingBall = velocity.x > 0.0f;

    if (mChasingBall)
    {
        SetTimeout(std::chrono::milliseconds(Random::ValueInRange(decisionTimeLowerBoundMs, decisionTimeUpperBoundMs)), [this] ()
        {
            this->PredictBallPostion();
        });
    }
}

} // namespace pong
