#pragma once

#include "sound.h"
#include "utils.h"

#include <portaudio.h>

#include <string>

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

int AudioCallbackWrapper(const void* inputBuffer, void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData);

} // namespace pong
