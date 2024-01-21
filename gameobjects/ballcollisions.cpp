#include "ballcollisions.h"

namespace pong
{

void BallCollisions::OnStart()
{
    mBall = GetComponent<BallMovement>();
    mBallAudio = GetComponent<BallAudio>();
}

void BallCollisions::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName().find("ScoreArea") != std::string::npos)
    {
        mBall->HitScoreArea();
        mBallAudio->HitScoreArea();
    }
    else if (other.GetInstanceName() == "Player" || other.GetInstanceName() == "Opponent")
    {
        mBall->HitPaddle(other);
        mBallAudio->HitPaddle();
    }
    else
    {
        mBall->HitWall();
        mBallAudio->HitWall();
    }
}

} // namespace pong
