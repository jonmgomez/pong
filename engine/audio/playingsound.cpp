#include "playingsound.h"

namespace pong
{

PlayingSound::PlayingSound(const Sound& sound) :
    mSound(&sound),
    mNumFrames(sound.GetAudioFile().getNumSamplesPerChannel())
{
}

PlayingSound::PlayingSound(const Sound& sound, const glm::vec3& position) :
    mSound(&sound),
    mNumFrames(sound.GetAudioFile().getNumSamplesPerChannel()),
    mPosition(position),
    mPositional(true)
{
}

int PlayingSound::GetNumChannels() const
{
    return mSound->GetAudioFile().getNumChannels();
}

float PlayingSound::GetSample(int channel) const
{
    return mSound->GetAudioFile().samples[channel][mIndex];
}

void PlayingSound::NextSample()
{
    mIndex++;
}

bool PlayingSound::IsFinished() const
{
    return mIndex >= mNumFrames;
}

glm::vec3 PlayingSound::GetPosition() const
{
    return mPosition;
}

bool PlayingSound::IsPositional() const
{
    return mPositional;
}

} // namespace pong
