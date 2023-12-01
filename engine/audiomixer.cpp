#include "audiomixer.h"

#include "config.h"
#include "logger.h"
#include "pong.h"
#include "sound.h"

#include <glm/glm.hpp>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>

namespace pong
{

static constexpr int SAMPLE_RATE = 44100;
static constexpr int FRAMES_PER_BUFFER = 256;
static constexpr glm::vec3 LEFT_LISTENER_POSITION = glm::vec3(-1125.0f, 0.0f, 0.0f);
static constexpr glm::vec3 RIGHT_LISTENER_POSITION = glm::vec3(1125.0f, 0.0f, 0.0f);
static constexpr float MIN_DISTANCE = 250.0f;

int AudioCallbackWrapper(const void* inputBuffer, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData)
{
    return Pong::GetInstance().GetAudioMixer().AudioCallback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags, userData);
}

void AudioMixer::Init()
{
    mVolume = Config::GetValue("volume", 0.5f);
    LogInfo("Volume: {}", mVolume);

    mSpatialAudioEnabled = Config::GetValue("spatial_audio", false);
    LogInfo("Spatial Audio: {}", mSpatialAudioEnabled ? "Enabled" : "Disabled");

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        LogError("PortAudio initialization failed: {}", Pa_GetErrorText(err));
    }

    const int kAudioChannelsStereo = 2;

    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = kAudioChannelsStereo;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    err = Pa_OpenStream(&mStream, nullptr, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, AudioCallbackWrapper, nullptr);
    if (err != paNoError) {
        LogError("PortAudio stream opening failed: {}", Pa_GetErrorText(err));
        Pa_Terminate();
        ASSERT(false);
    }

    err = Pa_StartStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream starting failed: {}", Pa_GetErrorText(err));
        Pa_CloseStream(mStream);
        Pa_Terminate();
        ASSERT(false);
    }
}

void AudioMixer::Cleanup()
{
    PaError err = Pa_StopStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream stopping failed: {}", Pa_GetErrorText(err));
        ASSERT(false);
        return;
    }

    err = Pa_CloseStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream closing failed: {}", Pa_GetErrorText(err));
        ASSERT(false);
        return;
    }

    Pa_Terminate();
}

void AudioMixer::PlaySound(const Sound& sound)
{
    mPlayingSoundsMutex.lock();
    mPlayingSounds.emplace_back(sound);
    mPlayingSoundsMutex.unlock();
}

void AudioMixer::PlaySound(const Sound& sound, const glm::vec3& position)
{
    mPlayingSoundsMutex.lock();
    mPlayingSounds.emplace_back(sound, position);
    mPlayingSoundsMutex.unlock();
}

int AudioMixer::AudioCallback(const void* /*inputBuffer*/, void* outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* /*timeInfo*/,
                              PaStreamCallbackFlags /*statusFlags*/,
                              void* /*userData*/)
{
    float* out = static_cast<float*>(outputBuffer);

    mPlayingSoundsMutex.lock();

    int frames = static_cast<int>(framesPerBuffer);
    for (int i = 0; i < frames; i++)
    {
        float sampleL = 0.0f;
        float sampleR = 0.0f;

        for (auto& sound : mPlayingSounds)
        {
            if (sound.IsFinished())
            {
                continue;
            }

            if (sound.GetNumChannels() >= 2)
            {
                sampleL += sound.GetSample(0);
                sampleR += sound.GetSample(1);
                sound.NextSample();
            }
            else
            {
                sampleL += sound.GetSample(0);
                sampleR += sound.GetSample(0);
                sound.NextSample();
            }

            if (mSpatialAudioEnabled && sound.IsPositional())
            {
                const glm::vec3 soundPosition = sound.GetPosition();
                const float leftDistance = glm::distance(LEFT_LISTENER_POSITION, soundPosition);
                const float rightDistance = glm::distance(RIGHT_LISTENER_POSITION, soundPosition);

                // calculate attenuation
                float leftAttenuation = 1.0f / (leftDistance / MIN_DISTANCE);
                float rightAttenuation = 1.0f / (rightDistance / MIN_DISTANCE);

                leftAttenuation = std::clamp(leftAttenuation, 0.0f, 1.0f);
                rightAttenuation = std::clamp(rightAttenuation, 0.0f, 1.0f);

                sampleL *= leftAttenuation;
                sampleR *= rightAttenuation;
            }
        }

        sampleL *= mVolume;
        sampleR *= mVolume;

        sampleL = std::clamp(sampleL, -1.0f, 1.0f);
        sampleR = std::clamp(sampleR, -1.0f, 1.0f);

        *out++ = sampleL;
        *out++ = sampleR;
    }

    mPlayingSounds.erase(std::remove_if(mPlayingSounds.begin(), mPlayingSounds.end(), [](const auto& sound) {
        return sound.IsFinished();
    }), mPlayingSounds.end());

    mPlayingSoundsMutex.unlock();

    return paContinue;
}

} // namespace pong
