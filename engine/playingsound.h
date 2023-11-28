#pragma once

#include "sound.h"

namespace pong
{

class PlayingSound
{
public:
    PlayingSound(const Sound& sound);

    float GetNextSample();
    bool IsFinished() const;

private:
    const Sound* mSound { nullptr };
    int mIndex {0};
    int mNumFrames {0};
};

} // namespace pong
