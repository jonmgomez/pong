#include "audiomixer.h"

#include "config.h"
#include "logger.h"
#include "pong.h"
#include "sound.h"

#include <AudioFile.h>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>

namespace pong
{

static constexpr int SAMPLE_RATE = 44100;
static constexpr int FRAMES_PER_BUFFER = 256;

auto lastTime = std::chrono::system_clock::now();

int AudioCallbackWrapper(const void* inputBuffer, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData)
{
    return Pong::GetInstance().GetAudioMixer().AudioCallback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags, userData);
}

bool AudioMixer::Init()
{
    mVolume = Config::GetValue("volume", 0.5f);
    LogInfo("Volume: {}", mVolume);

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        LogError("PortAudio initialization failed: {}", Pa_GetErrorText(err));
    }

    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2; // Stereo
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    err = Pa_OpenStream(&mStream, nullptr, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, AudioCallbackWrapper, nullptr);
    if (err != paNoError) {
        LogError("PortAudio stream opening failed: {}", Pa_GetErrorText(err));
        Pa_Terminate();
        return false;
    }

    err = Pa_StartStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream starting failed: {}", Pa_GetErrorText(err));
        Pa_CloseStream(mStream);
        Pa_Terminate();
        return false;
    }

    return true;
}

void AudioMixer::Cleanup()
{
    PaError err = Pa_StopStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream stopping failed: {}", Pa_GetErrorText(err));
        return;
    }

    err = Pa_CloseStream(mStream);
    if (err != paNoError) {
        LogError("PortAudio stream closing failed: {}", Pa_GetErrorText(err));
        return;
    }

    Pa_Terminate();
}

void AudioMixer::PlaySound(const Sound& sound)
{
    mPlayingSounds.emplace_back(sound);
}

int AudioMixer::AudioCallback(const void* /*inputBuffer*/, void* outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* /*timeInfo*/,
                              PaStreamCallbackFlags /*statusFlags*/,
                              void* /*userData*/)
{

    auto currentTime = std::chrono::system_clock::now();
    auto timeWaitedUs = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime);
    std::cout << "AudioCallback called with " << framesPerBuffer << " framesPerBuffer, and " << timeWaitedUs.count() << " us since last call\n";
    lastTime = currentTime;

    float* out = static_cast<float*>(outputBuffer);

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

            sampleL += sound.GetNextSample();
            sampleR += sampleL;
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

    return paContinue;
}

} // namespace pong
