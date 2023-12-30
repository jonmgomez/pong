#pragma once

#include "sound.h"

#include <glm/glm.hpp>

namespace pong
{

class PlayingSound
{
public:
    PlayingSound(const Sound& sound);
    PlayingSound(const Sound& sound, const glm::vec3& position);

    int GetNumChannels() const;
    float GetSample(int channel) const;
    void NextSample();
    bool IsFinished() const;
    glm::vec3 GetPosition() const;
    bool IsPositional() const;

private:
    const Sound* mSound { nullptr };
    int mIndex {0};
    int mNumFrames {0};
    glm::vec3 mPosition { glm::vec3(0.0f) };
    bool mPositional { false };
};

} // namespace pong
