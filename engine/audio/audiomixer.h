#pragma once

#include "playingsound.h"
#include "sound.h"
#include "utils.h"

#include <portaudio.h>

#include <atomic>
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
    void Reset();

    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);

    int AudioCallback(const void* inputBuffer, void* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void* userData);

    float GetVolume() const;
    void SetVolume(float volume);
    bool GetSpatialAudioEnabled() const;
    void SetSpatialAudioEnabled(bool enabled);

private:
    PaStream* mStream { nullptr };
    std::vector<PlayingSound> mPlayingSounds {};
    std::mutex mPlayingSoundsMutex {};
    std::atomic<float> mVolume { 0.75f };
    std::atomic<bool> mSpatialAudioEnabled { false };
};

} // namespace pong

namespace pong::globals::audio
{

extern AudioMixer* gAudioMixer;

AudioMixer* GetAudioMixerInstance();
void SetAudioMixerInstance(AudioMixer* audioMixer);

void PlaySound(const Sound& sound);
void PlaySound(const Sound& sound, const glm::vec3& position);

float GetVolume();
void SetVolume(float volume);
bool GetSpatialAudioEnabled();
void SetSpatialAudioEnabled(bool enabled);

} // namespace pong::globals::audio
