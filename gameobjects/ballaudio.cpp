#include "ballaudio.h"

#include "audiomixer.h"
#include "config.h"

namespace pong
{

void BallAudio::OnStart()
{
    mTransform = GetComponent<Transform>();
    mPaddleBounceSound.SetSource(Config::GetValue<std::string>("paddle_hit_sound"));
    mWallBounceSound.SetSource(Config::GetValue<std::string>("wall_hit_sound"));
    mScoreSound.SetSource(Config::GetValue<std::string>("score_sound"));
}

void BallAudio::HitScoreArea()
{
    globals::audio::PlaySound(mScoreSound, mTransform->mPosition);
}

void BallAudio::HitPaddle()
{
    globals::audio::PlaySound(mPaddleBounceSound, mTransform->mPosition);
}

void BallAudio::HitWall()
{
    globals::audio::PlaySound(mWallBounceSound, mTransform->mPosition);
}


} // namespace pong
