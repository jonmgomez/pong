#pragma once

#include "playingsound.h"
#include "sound.h"
#include "utils.h"

#include <portaudio.h>

#include <mutex>
#include <string>
#include <vector>

namespace pong
{

class AudioMixer
{
public:
    void Init();
    void Cleanup();

    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);

    int AudioCallback(const void* inputBuffer, void* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void* userData);

private:
    PaStream* mStream { nullptr };
    std::vector<PlayingSound> mPlayingSounds {};
    std::mutex mPlayingSoundsMutex {};
    float mVolume { 0.5f };
    bool mSpatialAudioEnabled { false };
};

} // namespace pong