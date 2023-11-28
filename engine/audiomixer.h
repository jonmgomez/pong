#pragma once

#include "playingsound.h"
#include "sound.h"
#include "utils.h"

#include <portaudio.h>

#include <string>

namespace pong
{

class AudioMixer
{
public:
    bool Init();
    void Cleanup();

    int AudioCallback(const void* inputBuffer, void* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void* userData);

    void PlaySound(const Sound& sound);

private:
    PaStream* mStream { nullptr };
    std::vector<PlayingSound> mPlayingSounds {};
    float mVolume { 0.5f };
};

} // namespace pong
