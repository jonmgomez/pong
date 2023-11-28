#include "playingsound.h"

namespace pong
{

PlayingSound::PlayingSound(const Sound& sound) :
    mSound(&sound),
    mNumFrames(sound.GetAudioFile().getNumSamplesPerChannel())
{
}

float PlayingSound::GetNextSample()
{
    if (mIndex >= mNumFrames)
    {
        return 0.0f;
    }

    const float sample = mSound->GetAudioFile().samples[0][mIndex];
    mIndex++;

    return sample;
}

bool PlayingSound::IsFinished() const
{
    return mIndex >= mNumFrames;
}

} // namespace pong
