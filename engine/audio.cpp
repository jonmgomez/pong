#include "audio.h"

#include "config.h"
#include "pong.h"

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>

namespace pong
{

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

auto lastTime = std::chrono::system_clock::now();

float volume = 0.35f;

AudioFile<float> audioFile;
AudioFile<float> audioFile2;
int numSamples = 0;
int currentSample = 0;

void ReadFile()
{
    audioFile.shouldLogErrorsToConsole(false);
    volume = Config::GetValue("volume", 0.35f);
    bool loaded = audioFile.load(Config::GetValue<std::string>("audio1"));
    if (!loaded)
    {
        std::cout << "Failed to load audio file" << std::endl;
    }

    if (audioFile.isMono())
    {
        std::cout << "Audio file is mono" << std::endl;
    }
    else if (audioFile.isStereo())
    {
        std::cout << "Audio file is stereo" << std::endl;
    }
    numSamples = audioFile.getNumSamplesPerChannel();
    std::cout << "Audio file has " << numSamples << " samples" << std::endl;

    loaded = audioFile2.load(Config::GetValue<std::string>("audio2"));
    if (!loaded)
    {
        std::cout << "Failed to load audio file" << std::endl;
    }
}

int AudioCallback(const void* inputBuffer, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData)
{
    return Pong::GetInstance().GetAudioMixer().AudioCallback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags, userData);
    // (void)timeInfo; // Unused
    // (void)statusFlags; // Unused
    // (void)userData; // Unused

    // auto currentTime = std::chrono::system_clock::now();
    // auto timeWaitedUs = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime);
    // std::cout << "AudioCallback called with " << framesPerBuffer << " framesPerBuffer, and " << timeWaitedUs.count() << " us since last call\n";
    // lastTime = currentTime;

    // if (timeWaitedUs.count() < 600)
    // {
    //     if (Config::GetValue("test", false))
    //     {
    //         std::cout << "returning" << std::endl;
    //         return paContinue;
    //     }
    // }

    // float* out = static_cast<float*>(outputBuffer);

    // int startSample = currentSample;
    // int frames = static_cast<int>(framesPerBuffer);
    // for (; currentSample < numSamples && currentSample - startSample < frames; currentSample++)
    // {
    //     float sampleL = (audioFile.samples[0][currentSample] + audioFile2.samples[0][currentSample]) * volume;
    //     float sampleR = (audioFile.samples[1][currentSample] + audioFile2.samples[1][currentSample]) * volume;

    //     sampleL = std::clamp(sampleL, -1.0f, 1.0f);
    //     sampleR = std::clamp(sampleR, -1.0f, 1.0f);

    //     *out++ = sampleL;
    //     *out++ = sampleR;
    // }

    // // Simple example: Generate a stereo signal with different tones for left and right channels
    // for (unsigned int i = 0; i < framesPerBuffer; ++i) {
    //     // Left channel: 440 Hz sine wave
    //     *out++ = 0.5f * static_cast<float>(std::sin(2.0 * 3.14159265359 * 480.0 * i / SAMPLE_RATE)) * volume;

    //     // Right channel: 880 Hz sine wave
    //     *out++ = 0; // 0.5f * static_cast<float>(std::sin(2.0 * 3.14159265359 * 440.0 * i / SAMPLE_RATE));
    // }

    //return paContinue;
}

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

Sound::Sound(const std::string& filePath)
{
    mAudioFile.shouldLogErrorsToConsole(false);

    ASSERT(mAudioFile.load(filePath));
}

const AudioFile<float>& Sound::GetAudioFile() const
{
    return mAudioFile;
}

void AudioMixer::PlaySound(const Sound& sound)
{
    mPlayingSounds.emplace_back(sound);
}

int AudioMixer::AudioCallback(const void* /*inputBuffer*/, void* outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void* userData)
{
    (void)timeInfo; // Unused
    (void)statusFlags; // Unused
    (void)userData; // Unused

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

        sampleL *= volume;
        sampleR *= volume;

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
